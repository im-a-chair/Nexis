#include "ECS.h"
#include "std.h"
#include "Log.h"

/** TODO:
 * simplefy component pool struct into void** to directly pass to systems
 *  - this means the system running approach can be more flexible,
 *    since it no longer needs the stack locality
 * remove `is_active` array for entities in favor of the free list
 * merge entity free list capacity and entity capacity
 * implement an incremental query cache update;
 *  - When a new archetype is created (or an entity changes archetype),
 *    you only need to check that one new archetype against all existing queries.
 */

#define NXS_ECS_DEFAULT_ARCHETYPE_CAPACITY 16

struct NXS_ECS_ComponentType_T {
    uint32_t id;
    const char* name;
    size_t size;
    NXS_ECS_Constructor constructor; // Is NULL if not used.
    NXS_ECS_Destructor destructor; // Is NULL if not used.
};
struct NXS_ECS_ComponentPool {
    uint32_t type_id;
    size_t typesize;
    void* data;
};
struct NXS_ECS_Archetype {
    struct NXS_ECS_ComponentPool* pools; //parallel to / uses same indexing as `types`
    size_t pool_count;
    NXS_ECS_Entity* entity_ids; //parallel to `data` per pool
    size_t capacity; //of entities
    size_t count; //of entities
};
struct NXS_ECS_EntityData {
    struct NXS_ECS_Archetype* archetype;
    NXS_ECS_Entity index; //for `archetype->pools[type].data` and `archetype->entity_ids` arrays
};
struct NXS_ECS_Query_T {
    uint32_t id;
    uint32_t* req_types; //required types, by id
    size_t req_count;
    uint32_t* exc_types; //component types to exclude, by id
    size_t exc_count;

    //query cache, funtions like create/destroy entity and add/remove component should call an update for this cache
    struct NXS_ECS_Archetype** archetypes;
    size_t arch_count;
    size_t arch_capacity;
};
struct NXS_ECS_System_T {
    uint32_t id;
    NXS_ECS_SystemStage stage;
    NXS_ECS_Query* query; //pointer to the query to use
    NXS_ECS_SystemFunc function;
};
struct NXS_ECS_World_T {
    struct {
        NXS_ECS_Entity entity_count; // id of the next entity (DO NOT DECREMENT upon Entity destruction, would mess up array indexing)
        NXS_ECS_Entity capacity; //for `is_active` and `data` arrays
        bool* is_active; // a boolean array indexed by the entity value, if false the entity has been destroyed/deallocated/freed
        struct NXS_ECS_EntityData* data; //to find archetype per entity
        uint32_t* free_ids; //unused ids that are less than `count`
        size_t free_capacity;
        size_t free_count;
    } entities;
    struct {
        NXS_ECS_ComponentType* types; // Dynamic array of ComponentTypes
        size_t capacity;
        size_t count;
        uint32_t* free_ids; //unused ids that are less than `count`
        size_t free_capacity;
        size_t free_count;
    } types;
    struct {
        struct NXS_ECS_Archetype* archetypes;
        size_t capacity;
        size_t count;
    } archetypes;
    struct {
        NXS_ECS_Query* queries;
        size_t capacity;
        size_t count;
        uint32_t* free_ids; //unused ids that are less than `count`
        size_t free_capacity;
        size_t free_count;
    } queries;
    struct {
        struct {
            NXS_ECS_System* systems;
            size_t capacity;
            size_t count; //for next id
            uint32_t* free_ids; //unused ids that are less than `count`
            size_t free_capacity;
            size_t free_count;
        } input;
        struct {
            NXS_ECS_System* systems;
            size_t capacity;
            size_t count; //for next id
            uint32_t* free_ids; //unused ids that are less than `count`
            size_t free_capacity;
            size_t free_count;
        } proc;
        struct {
            NXS_ECS_System* systems;
            size_t capacity;
            size_t count; //for next id
            uint32_t* free_ids; //unused ids that are less than `count`
            size_t free_capacity;
            size_t free_count;
        } output;
        struct {
            NXS_ECS_System* systems;
            size_t capacity;
            size_t count; //for next id
            uint32_t* free_ids; //unused ids that are less than `count`
            size_t free_capacity;
            size_t free_count;
        } manual;
    } systems;
};

int _nxis_compare_by_id(const void* a, const void* b) {
    return ((*(const NXS_ECS_ComponentType* const*)a)->id - (*(const NXS_ECS_ComponentType* const*)b)->id);
}
static inline struct NXS_ECS_Archetype* _nxis_find_or_create_archetype(NXS_ECS_World* world, NXS_ECS_ComponentType* sorted_types[], size_t type_count) {
    NXS_ASSERT(world);
    NXS_ASSERT(sorted_types);
    NXS_ASSERT(type_count != 0);

    size_t archetype_index = -1;
    bool match_found = false;

    //check if a match exists
    for (size_t i = 0; i < world->archetypes.count; ++i) {
        struct NXS_ECS_Archetype* current_arch = &world->archetypes.archetypes[i];

        if (current_arch->pool_count != type_count) {
            continue;
        }

        bool match = true;
        //compare the sorted component lists
        for (size_t j = 0; j < type_count; ++j) {
            if (current_arch->pools[j].type_id != sorted_types[j]->id) {
                match = false;
                break; //mismatch found, break inner loop
            }
        }

        if (match) {
            archetype_index = i;
            match_found = true;
            break; //archetype found, break outer loop
        }
    }

    //if not, make one
    if (archetype_index == (size_t)-1) {
        if (world->archetypes.count >= world->archetypes.capacity) {
            struct NXS_ECS_Archetype* new_archetypes = (struct NXS_ECS_Archetype*)realloc(world->archetypes.archetypes, sizeof(struct NXS_ECS_Archetype) * world->archetypes.capacity * 2);
            if (!new_archetypes) {
                NXS_Error(strerror(errno));
                return NULL;
            }
            world->archetypes.archetypes = new_archetypes;
            world->archetypes.capacity *= 2;
        }

        struct NXS_ECS_Archetype* new_arch = &world->archetypes.archetypes[world->archetypes.count];

        new_arch->pools = (struct NXS_ECS_ComponentPool*)calloc(type_count, sizeof(struct NXS_ECS_ComponentPool));
        if (!new_arch->pools) {
            NXS_Error(strerror(errno));
            return NULL;
        }

        new_arch->entity_ids = (NXS_ECS_Entity*)calloc(NXS_ECS_DEFAULT_ARCHETYPE_CAPACITY, sizeof(NXS_ECS_Entity));
        if (!new_arch->entity_ids) {
            free(new_arch->pools);
            NXS_Error(strerror(errno));
            return NULL;
        }
        
        new_arch->pool_count = type_count;
        new_arch->capacity = NXS_ECS_DEFAULT_ARCHETYPE_CAPACITY;
        new_arch->count = 0;

        for (size_t i = 0; i < type_count; i++) {
            new_arch->pools[i].type_id = sorted_types[i]->id;
            new_arch->pools[i].typesize = sorted_types[i]->size;
            if (new_arch->pools[i].typesize != 0) {
                new_arch->pools[i].data = calloc(new_arch->capacity, new_arch->pools[i].typesize);
                if (!new_arch->pools[i].data) {
                    for (size_t j = 0; j < i; j++) {
                        free(new_arch->pools[j].data);
                    }
                    free(new_arch->entity_ids);
                    free(new_arch->pools);
                    NXS_Error(strerror(errno));
                    return NULL;
                }
            } else {
                new_arch->pools[i].data = NULL; //to prevent memory access to random non-NULL pointer
            }
        }
        archetype_index = world->archetypes.count++;
    }

    //assign
    struct NXS_ECS_Archetype* archetype = &world->archetypes.archetypes[archetype_index];

    //resize archetype if count exceeds capacity
    if (archetype->count >= archetype->capacity) {
        size_t new_capacity = archetype->capacity * 2;

        NXS_ECS_Entity* new_ids = (NXS_ECS_Entity*)realloc(archetype->entity_ids, new_capacity * sizeof(NXS_ECS_Entity));
        if (!new_ids) {
            NXS_Error(strerror(errno));
            return NULL;
        }
        archetype->entity_ids = new_ids;

        for (size_t i = 0; i < archetype->pool_count; ++i) {
            if (archetype->pools[i].typesize != 0) {
                void* new_data = realloc(archetype->pools[i].data, new_capacity * archetype->pools[i].typesize);
                if (!new_data) {
                    NXS_Error(strerror(errno));
                    return NULL;
                }
                archetype->pools[i].data = new_data;
            }
        }
        archetype->capacity = new_capacity;
    }

    return archetype;
}
static inline void _nxis_call_constructors(NXS_ECS_World* world, struct NXS_ECS_Archetype* archetype, NXS_ECS_Entity entity) {
    for (size_t i = 0; i < archetype->pool_count; i++) {
        NXS_ECS_ComponentType* type = NXS_ECS_GetComponentTypeById(world, archetype->pools[i].type_id);
        if (type && type->constructor) {
            void* component_data_ptr = (char*)archetype->pools[i].data + (world->entities.data[entity].index * archetype->pools[i].typesize);
            type->constructor(world, entity, type, component_data_ptr);
        }
    }
}
static inline void _nxis_call_destructors(NXS_ECS_World* world, struct NXS_ECS_Archetype* archetype, NXS_ECS_Entity entity) {
    for (size_t i = 0; i < archetype->pool_count; ++i) {
        NXS_ECS_ComponentType* type = NXS_ECS_GetComponentTypeById(world, archetype->pools[i].type_id);
        if (type && type->destructor) {
            void* component_data_ptr = (char*)archetype->pools[i].data + (world->entities.data[entity].index * archetype->pools[i].typesize);
            type->destructor(world, entity, type, component_data_ptr);
        }
    }
}
static inline void _nxis_kill_archetype_if_empty(NXS_ECS_World* world, struct NXS_ECS_Archetype* archetype) {
    NXS_ASSERT(world);
    NXS_ASSERT(archetype);

    if (archetype->count > 0) {
        return; //not empty
    }

    //deallocate archetype component pools
    for (size_t i = 0; i < archetype->pool_count; ++i) {
        if (archetype->pools[i].data) {
            free(archetype->pools[i].data);
        }
    }
    free(archetype->pools);
    free(archetype->entity_ids);

    //find the index of the archetype to be removed
    size_t archetype_index = -1;
    for (size_t i = 0; i < world->archetypes.count; ++i) {
        if (&world->archetypes.archetypes[i] == archetype) {
            archetype_index = i;
            break;
        }
    }

    //if a match was found, perform a swap-and-pop
    if (archetype_index != (size_t)-1) {
        size_t last_archetype_index = world->archetypes.count - 1;
        
        //if the archetype to be removed is not the last one, move the last one into its place
        if (archetype_index != last_archetype_index) {
            world->archetypes.archetypes[archetype_index] = world->archetypes.archetypes[last_archetype_index];
        }

        //decrement the archetype count
        world->archetypes.count--;
    }
}
static inline void _nxis_remove_entity_from_archetype(NXS_ECS_World* world, struct NXS_ECS_Archetype* archetype, NXS_ECS_Entity entity) {
    struct NXS_ECS_EntityData* entity_data = &world->entities.data[entity];
    size_t removed_index = entity_data->index;

    // Get the ID and index of the last entity in the archetype
    size_t last_index = archetype->count - 1;
    NXS_ECS_Entity last_entity_id = archetype->entity_ids[last_index];

    // If the entity to be removed is not the last one, perform the swap
    if (removed_index != last_index) {
        // Move all component data from the last entity to the removed entity's slot
        for (size_t i = 0; i < archetype->pool_count; ++i) {
            if (archetype->pools[i].typesize == 0) {
                continue; //for tags
            }
            void* component_pool = archetype->pools[i].data;
            size_t component_size = archetype->pools[i].typesize;

            // Pointers to the two component instances
            void* last_entity_data_ptr = (char*)component_pool + (last_index * component_size);
            void* removed_entity_data_ptr = (char*)component_pool + (removed_index * component_size);

            // Copy the data from the last entity to the removed entity's position
            memcpy(removed_entity_data_ptr, last_entity_data_ptr, component_size);
        }

        // Update the archetype's entity ID array
        archetype->entity_ids[removed_index] = last_entity_id;

        // Update the lookup table for the swapped entity
        world->entities.data[last_entity_id].index = removed_index;
    }

    archetype->count--;
}
static inline struct NXS_ECS_ComponentPool* _nxis_find_component_pool(struct NXS_ECS_Archetype* archetype, uint32_t id) {
    for (size_t i = 0; i < archetype->pool_count; i++) {
        if (archetype->pools[i].type_id == id) {
            return &archetype->pools[i];
        }
    }
    return NULL;
}
static inline bool _nxis_archetype_matches_query(struct NXS_ECS_Archetype* arch, NXS_ECS_Query* query) {
    //two-pointer walk to check for required types
    size_t arch_pool_idx = 0;
    for (size_t k = 0; k < query->req_count; ++k) {
        uint32_t required_type_id = query->req_types[k];
        while (arch_pool_idx < arch->pool_count && arch->pools[arch_pool_idx].type_id < required_type_id) {
            arch_pool_idx++;
        }
        if (arch_pool_idx >= arch->pool_count || arch->pools[arch_pool_idx].type_id != required_type_id) {
            return false; //required component not found
        }
        arch_pool_idx++;
    }

    //two-pointer walk to check for excluded types
    arch_pool_idx = 0;
    for (size_t k = 0; k < query->exc_count; ++k) {
        uint32_t excluded_type_id = query->exc_types[k];
        while (arch_pool_idx < arch->pool_count && arch->pools[arch_pool_idx].type_id < excluded_type_id) {
            arch_pool_idx++;
        }
        if (arch_pool_idx < arch->pool_count && arch->pools[arch_pool_idx].type_id == excluded_type_id) {
            return false; //excluded component found
        }
    }

    return true; //archetype matches both required and excluded lists
}

NXS_ECS_World* NXS_ECS_CreateWorld(size_t init_cap) {
    NXS_ASSERT(init_cap != 0);
    NXS_ECS_World* world = (NXS_ECS_World*)calloc(1, sizeof(NXS_ECS_World));
    if (!world) {
        NXS_Error(strerror(errno));
        return NULL;
    }

    // Initialize entity array (is_active)
    world->entities.is_active = (bool*)calloc(init_cap, sizeof(bool));
    if (!world->entities.is_active) {
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->entities.data = (struct NXS_ECS_EntityData*)calloc(init_cap, sizeof(struct NXS_ECS_EntityData));
    if (!world->entities.data) {
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->entities.free_ids = (uint32_t*)calloc(init_cap, sizeof(uint32_t));
    if (!world->entities.free_ids) {
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->entities.capacity = world->entities.free_capacity = init_cap;
    world->entities.entity_count = world->entities.free_count = 0;
    world->entities.is_active[0] = false;
    world->entities.data[0].archetype = NULL;
    world->entities.data[0].index = 0;

    // Initialize component types array
    world->types.types = (NXS_ECS_ComponentType*)calloc(init_cap, sizeof(NXS_ECS_ComponentType));
    if (!world->types.types) {
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->types.free_ids = (uint32_t*)calloc(init_cap, sizeof(uint32_t));
    if (!world->types.free_ids) {
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->types.count = world->types.free_count = 0;
    world->types.capacity = world->types.free_capacity = init_cap;

    // Initialize archetype array
    world->archetypes.archetypes = (struct NXS_ECS_Archetype*)calloc(init_cap, sizeof(struct NXS_ECS_Archetype));
    if (!world->archetypes.archetypes) {
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->archetypes.capacity = init_cap;
    world->archetypes.count = 0;

    // Initialize queries array
    world->queries.queries = (NXS_ECS_Query*)calloc(init_cap, sizeof(NXS_ECS_Query));
    if (!world->queries.queries) {
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->queries.free_ids = (uint32_t*)calloc(init_cap, sizeof(uint32_t));
    if (!world->queries.free_ids) {
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->queries.count = world->queries.free_count = 0;
    world->queries.capacity = world->queries.free_capacity = init_cap;

    // Initialize system arrays (using a default small capacity)
    world->systems.input.free_capacity = world->systems.input.capacity = init_cap / 4;
    world->systems.input.systems = (NXS_ECS_System*)calloc(world->systems.input.capacity, sizeof(NXS_ECS_System));
    if (!world->systems.input.systems) {
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.input.free_ids = (uint32_t*)calloc(world->systems.input.free_capacity, sizeof(uint32_t));
    if (!world->systems.input.free_ids) {
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.input.free_count = world->systems.input.count = 0;

    world->systems.proc.capacity = world->systems.proc.free_capacity = init_cap / 4;
    world->systems.proc.systems = (NXS_ECS_System*)calloc(world->systems.proc.capacity, sizeof(NXS_ECS_System));
    if (!world->systems.proc.systems) {
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.proc.free_ids = (uint32_t*)calloc(world->systems.proc.free_capacity, sizeof(uint32_t));
    if (!world->systems.proc.free_ids) {
        free(world->systems.proc.systems);
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.proc.count = world->systems.proc.free_count = 0;

    world->systems.output.capacity = world->systems.output.free_capacity = init_cap / 4;
    world->systems.output.systems = (NXS_ECS_System*)calloc(world->systems.output.capacity, sizeof(NXS_ECS_System));
    if (!world->systems.output.systems) {
        free(world->systems.proc.free_ids);
        free(world->systems.proc.systems);
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.output.free_ids = (uint32_t*)calloc(world->systems.output.free_capacity, sizeof(uint32_t));
    if (!world->systems.output.free_ids) {
        free(world->systems.output.systems);
        free(world->systems.proc.free_ids);
        free(world->systems.proc.systems);
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.output.count = 0;

    world->systems.manual.capacity = init_cap / 4;
    world->systems.manual.systems = (NXS_ECS_System*)calloc(world->systems.manual.capacity, sizeof(NXS_ECS_System));
    if (!world->systems.manual.systems) {
        free(world->systems.output.free_ids);
        free(world->systems.output.systems);
        free(world->systems.proc.free_ids);
        free(world->systems.proc.systems);
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.manual.free_ids = (uint32_t*)calloc(world->systems.manual.free_capacity, sizeof(uint32_t));
    if (!world->systems.manual.free_ids) {
        free(world->systems.manual.systems);
        free(world->systems.output.free_ids);
        free(world->systems.output.systems);
        free(world->systems.proc.free_ids);
        free(world->systems.proc.systems);
        free(world->systems.input.free_ids);
        free(world->systems.input.systems);
        free(world->queries.free_ids);
        free(world->queries.queries);
        free(world->archetypes.archetypes);
        free(world->types.free_ids);
        free(world->types.types);
        free(world->entities.free_ids);
        free(world->entities.data);
        free(world->entities.is_active);
        free(world);
        NXS_Error(strerror(errno));
        return NULL;
    }
    world->systems.manual.count = 0;

    return world;
}
void NXS_ECS_DestroyWorld(NXS_ECS_World* world) {
    if (!world) {
        return;
    }
    for (size_t i = 0; i < world->archetypes.count; ++i) {
        struct NXS_ECS_Archetype* archetype = &world->archetypes.archetypes[i];
        if (archetype->entity_ids) {
            free(archetype->entity_ids);
        }
        if (archetype->pools) {
            // Free component pool data and entity ID arrays
            for (size_t j = 0; j < archetype->pool_count; ++j) {
                free(archetype->pools[j].data);
            }
            free(archetype->pools);
        }
    }
    free(world->archetypes.archetypes);
    for (size_t i = 0; i < world->queries.count; ++i) {
        free(world->queries.queries[i].req_types);
        free(world->queries.queries[i].exc_types);
        // The archetypes pointer array is temporary and not freed here
    }
    free(world->queries.free_ids);
    free(world->queries.queries);
    free(world->systems.input.free_ids);
    free(world->systems.input.systems);
    free(world->systems.proc.free_ids);
    free(world->systems.proc.systems);
    free(world->systems.output.free_ids);
    free(world->systems.output.systems);
    free(world->systems.manual.free_ids);
    free(world->systems.manual.systems);
    free(world->types.free_ids);
    free(world->types.types);
    free(world->entities.free_ids);
    free(world->entities.data);
    free(world->entities.is_active);
    free(world);
}
inline uint32_t NXS_ECS_GetEntityCount(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    return world->entities.entity_count - world->entities.free_count;
}
inline uint32_t NXS_ECS_GetComponentTypeCount(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    return world->types.count - world->types.free_count;
}
inline uint32_t NXS_ECS_GetArchetypeCount(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    return world->archetypes.count;
}
inline uint32_t NXS_ECS_GetQueryCount(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    return world->queries.count - world->queries.free_count;
}
inline uint32_t NXS_ECS_GetSystemCount(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    return (
        world->systems.input.count + 
        world->systems.proc.count + 
        world->systems.output.count + 
        world->systems.manual.count
    ) - (
        world->systems.input.free_count + 
        world->systems.proc.free_count + 
        world->systems.output.free_count + 
        world->systems.manual.free_count
    );
}
NXS_ECS_Entity NXS_ECS_CreateEntity(NXS_ECS_World* world) {
    NXS_ASSERT(world);

    NXS_ECS_Entity entity_id;

    //resize if count exceeds capacity
    if (world->entities.free_count == 0 && world->entities.entity_count >= world->entities.capacity) {
        size_t new_capacity = world->entities.capacity * 2;

        bool* new_is_active = (bool*)realloc(world->entities.is_active, sizeof(bool) * new_capacity);
        if (!new_is_active) {
            NXS_Error(strerror(errno));
            return 0;
        }
        world->entities.is_active = new_is_active;

        struct NXS_ECS_EntityData* new_data = (struct NXS_ECS_EntityData*)realloc(world->entities.data, sizeof(struct NXS_ECS_EntityData) * new_capacity);
        if (!new_data) {
            NXS_Error(strerror(errno));
            return 0;
        }
        world->entities.data = new_data;

        uint32_t* new_fids = (uint32_t*)realloc(world->entities.free_ids, sizeof(uint32_t) * new_capacity);
        if (!new_fids) {
            NXS_Error(strerror(errno));
            return 0;
        }
        world->entities.free_ids = new_fids;

        world->entities.capacity = new_capacity;
    }

    //if there are free spaces, use one
    if (world->entities.free_count > 0) {
        entity_id = world->entities.free_ids[--world->entities.free_count];
    } else {
        entity_id = world->entities.entity_count++;
    }

    // At this point, the entity has a unique ID, but no components.
    // it is not yet part of an archetype, until a first component is added

    world->entities.data[entity_id].archetype = NULL;
    world->entities.data[entity_id].index = 0;
    world->entities.is_active[entity_id] = true;
    return entity_id;
}
NXS_ECS_Entity NXS_ECS_CreateEntityWithComponents(NXS_ECS_World* world, NXS_ECS_ComponentType* types[], size_t type_count) {
    NXS_ASSERT(world);
    NXS_ASSERT(types);
    NXS_ASSERT(type_count != 0);

    //sort the input `types` array by component id
    NXS_ECS_ComponentType* sorted_types[type_count];
    memcpy(sorted_types, types, type_count * sizeof(NXS_ECS_ComponentType*));
    qsort(sorted_types, type_count, sizeof(NXS_ECS_ComponentType*), _nxis_compare_by_id);

    //get the archetype
    struct NXS_ECS_Archetype* archetype = _nxis_find_or_create_archetype(world, sorted_types, type_count);

    //now, create the entity and add it
    NXS_ECS_Entity entity_id = NXS_ECS_CreateEntity(world);

    //add the new entity's ID to the archetype's entity_ids array
    archetype->entity_ids[archetype->count] = entity_id;

    //call constructors for each component
    _nxis_call_constructors(world, archetype, entity_id);

    world->entities.data[entity_id].archetype = archetype;
    world->entities.data[entity_id].index = archetype->count++;
    return entity_id;
}
void NXS_ECS_DestroyEntity(NXS_ECS_World* world, NXS_ECS_Entity entity) {
    NXS_ASSERT(world);
    NXS_ASSERT(entity != 0);
    NXS_ASSERT(world->entities.is_active[entity]);
    
    _nxis_remove_entity_from_archetype(world, world->entities.data[entity].archetype, entity);

    world->entities.is_active[entity] = false;
    world->entities.free_ids[world->entities.free_count++] = entity;

    _nxis_kill_archetype_if_empty(world, world->entities.data[entity].archetype);

    return;
}
NXS_ECS_ComponentType* NXS_ECS_CreateComponentType(NXS_ECS_World* world, const char* name, size_t size, NXS_ECS_Constructor constructor, NXS_ECS_Destructor destructor) {
    NXS_ASSERT(world);
    NXS_ASSERT(name);
    //NXS_ASSERT(size != 0); //would be tag

    uint32_t new_id;

    //check for free spaces
    if (world->types.free_count > 0) {
        new_id = world->types.free_ids[--world->types.free_count];
    } else {
        //realloc if needed
        if (world->types.count >= world->types.capacity) {
            NXS_ECS_ComponentType* new = (NXS_ECS_ComponentType*)realloc(world->types.types, sizeof(NXS_ECS_ComponentType) * world->types.capacity * 2);
            if (!new) {
                NXS_Error(strerror(errno));
                return NULL;
            }
            world->types.capacity *= 2;
        }

        new_id = world->types.count++;
    }

    world->types.types[new_id].name = (char*)calloc(1, strlen(name) + 1);
    if (!world->types.types[new_id].name) {
        NXS_Error(strerror(errno));
        return NULL;
    }
    strcpy(world->types.types[new_id].name, name);

    world->types.types[new_id].id = new_id;
    world->types.types[new_id].size = size;
    world->types.types[new_id].constructor = constructor;
    world->types.types[new_id].destructor = destructor;
    return &world->types.types[new_id];
}
void NXS_ECS_DestroyComponentType(NXS_ECS_World* world, NXS_ECS_ComponentType* type) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(world->types.types[type->id].name);

    //query all entities with component of this type
        //run `NXS_ECS_RemoveComponent` on each
    uint32_t typeid = type->id; //for stack locality, to optimize the following loop
    for (size_t i = 0; i < world->archetypes.count; i++) {
        for(size_t j = 0; j < world->archetypes.archetypes[i].pool_count; j++) {
            if (world->archetypes.archetypes[i].pools[j].type_id == typeid) {
                for (size_t k = 0; k < world->archetypes.archetypes[i].count; k++) {
                    NXS_ECS_RemoveComponent(world, type, world->archetypes.archetypes[i].entity_ids[k], false);
                }
            }
        }
    }

    world->types.types[type->id].size = 0;
    world->types.types[type->id].constructor = NULL;
    world->types.types[type->id].destructor = NULL;
    free(world->types.types[type->id].name);

    world->types.free_ids[world->types.free_count++] = type->id;

    return;
}
inline const char* NXS_ECS_GetComponentTypeName(NXS_ECS_ComponentType* type) {
    NXS_ASSERT(type);
    NXS_ASSERT(type->name);
    return type->name;
}
inline uint32_t NXS_ECS_GetComponentTypeId(NXS_ECS_ComponentType* type) {
    NXS_ASSERT(type);
    return type->id;
}
inline size_t NXS_ECS_GetComponentTypeSize(NXS_ECS_ComponentType* type) {
    NXS_ASSERT(type);
    return type->size;
}
NXS_ECS_ComponentType* NXS_ECS_GetComponentTypeByName(NXS_ECS_World* world, const char* name) {
    NXS_ASSERT(world);
    NXS_ASSERT(name);
    for (size_t i = 0; i < world->types.count; i++) {
        if (strcmp(world->types.types[i].name, name) == 0) {
            return &world->types.types[i];
        }
    }
    return NULL;
}
inline NXS_ECS_ComponentType* NXS_ECS_GetComponentTypeById(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    NXS_ASSERT(world->types.types[id].name);
    return &world->types.types[id];
}
inline void NXS_ECS_SetConstructor(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Constructor constructor) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(world->types.types[type->id].name);
    world->types.types[type->id].constructor = constructor;
    return;
}
inline void NXS_ECS_SetDestructor(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Destructor destructor) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(world->types.types[type->id].name);
    world->types.types[type->id].destructor = destructor;
    return;
}
bool NXS_ECS_AddComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, void* initial_data, bool ignore_constructor) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(entity != 0);

    struct NXS_ECS_Archetype* old_archetype = world->entities.data[entity].archetype;

    //get entity types as array
    size_t type_count = old_archetype->pool_count + 1;
    NXS_ECS_ComponentType* sorted_types[type_count];
    for (size_t i = 0; i < type_count-1; i++) {
        sorted_types[i] = &world->types.types[old_archetype->pools[i].type_id];
    }
    //append new type
    sorted_types[type_count-1] = type;
    //sort the input `types` array by component id
    qsort(sorted_types, type_count, sizeof(NXS_ECS_ComponentType*), _nxis_compare_by_id);

    struct NXS_ECS_Archetype* new_archetype = _nxis_find_or_create_archetype(world, sorted_types, type_count);

    //get the entity's old index and the new index
    size_t old_index = world->entities.data[entity].index;
    size_t new_index = new_archetype->count;

    //copy existing component data from old archetype to new archetype
    int old_pool_idx = 0;
    int new_pool_idx = 0;
    while(old_pool_idx < old_archetype->pool_count && new_pool_idx < new_archetype->pool_count) {
        if(old_archetype->pools[old_pool_idx].type_id == new_archetype->pools[new_pool_idx].type_id) {
            //found a matching component type, copy its data from the old to the new location
            memcpy(
                (char*)new_archetype->pools[new_pool_idx].data + new_index * new_archetype->pools[new_pool_idx].typesize,
                (char*)old_archetype->pools[old_pool_idx].data + old_index * old_archetype->pools[old_pool_idx].typesize,
                old_archetype->pools[old_pool_idx].typesize
            );
            old_pool_idx++;
            new_pool_idx++;
        } else if(old_archetype->pools[old_pool_idx].type_id < new_archetype->pools[new_pool_idx].type_id) {
            old_pool_idx++;
        } else {
            new_pool_idx++;
        }
    }

    //initialize the data for the newly added component
    struct NXS_ECS_ComponentPool* new_pool = _nxis_find_component_pool(new_archetype, type->id);
    if(new_pool) {
        //get pointer to the new component instance
        void* new_component = (char*)new_pool->data + new_index * new_pool->typesize;
        
        if (initial_data) {
            memcpy(new_component, initial_data, type->size);
        }

        if (!ignore_constructor && type->constructor) {
            type->constructor(world, entity, type, new_component);
        }
    }

    //now that the data is copied, move the entity into the new archetype
    new_archetype->entity_ids[new_index] = entity;
    world->entities.data[entity].archetype = new_archetype;
    world->entities.data[entity].index = new_index;
    new_archetype->count++;

    //remove the entity from the old archetype
    _nxis_remove_entity_from_archetype(world, old_archetype, entity);

    //annihilate old archetype if empty
    _nxis_kill_archetype_if_empty(world, old_archetype);

    return true;
}
bool NXS_ECS_RemoveComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, bool ignore_destructor) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(entity != 0);

    struct NXS_ECS_Archetype* old_archetype = world->entities.data[entity].archetype;

    //check if the entity has the component to remove
    struct NXS_ECS_ComponentPool* old_component_pool = _nxis_find_component_pool(old_archetype, type->id);
    if (!old_component_pool) {
        return false; //the entity does not have this component
    }

    //prepare the list of types for the new archetype
    size_t type_count = old_archetype->pool_count - 1;
    NXS_ECS_ComponentType* sorted_types[type_count];
    int new_type_idx = 0;
    for (size_t i = 0; i < old_archetype->pool_count; i++) {
        if (old_archetype->pools[i].type_id != type->id) {
            sorted_types[new_type_idx++] = &world->types.types[old_archetype->pools[i].type_id];
        }
    }

    //find or create the new archetype
    struct NXS_ECS_Archetype* new_archetype = _nxis_find_or_create_archetype(world, sorted_types, type_count);

    //get the entity's old index and the new index in the destination archetype
    size_t old_index = world->entities.data[entity].index;
    size_t new_index = new_archetype->count;

    //call the destructor if it exists, before the component data is moved/lost
    if (!ignore_destructor && type->destructor) {
        type->destructor(world, entity, type, (char*)old_component_pool->data + old_index * old_component_pool->typesize);
    }
    
    //copy existing component data from the old archetype to the new archetype
    int old_pool_idx = 0;
    int new_pool_idx = 0;
    while(old_pool_idx < old_archetype->pool_count && new_pool_idx < new_archetype->pool_count) {
        //skip the removed component in the old archetype
        if (old_archetype->pools[old_pool_idx].type_id == type->id) {
            old_pool_idx++;
            continue;
        }

        //copy the data for the components that remain
        memcpy(
            (char*)new_archetype->pools[new_pool_idx].data + new_index * new_archetype->pools[new_pool_idx].typesize,
            (char*)old_archetype->pools[old_pool_idx].data + old_index * old_archetype->pools[old_pool_idx].typesize,
            old_archetype->pools[old_pool_idx].typesize
        );
        old_pool_idx++;
        new_pool_idx++;
    }

    //move the entity into the new archetype
    new_archetype->entity_ids[new_index] = entity;
    world->entities.data[entity].archetype = new_archetype;
    world->entities.data[entity].index = new_index;
    new_archetype->count++;

    //remove the entity from the old archetype
    _nxis_remove_entity_from_archetype(world, old_archetype, entity);

    //annihilate old archetype if empty
    _nxis_kill_archetype_if_empty(world, old_archetype);
    
    return true;
}
inline const void* NXS_ECS_GetComponentData(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(entity != 0);

    struct NXS_ECS_EntityData* entity_data = &world->entities.data[entity];
    struct NXS_ECS_Archetype* archetype = entity_data->archetype;
    size_t entity_index = entity_data->index;

    struct NXS_ECS_ComponentPool* pool = _nxis_find_component_pool(archetype, type->id);
    if (!pool) {
        return NULL; //entity doesnt have component of type
    }

    return (const char*)pool->data + (entity_index * pool->typesize);
}
inline bool NXS_SetComponentData(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, void* new_data) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(entity != 0);
    NXS_ASSERT(new_data);

    struct NXS_ECS_EntityData* entity_data = &world->entities.data[entity];
    struct NXS_ECS_Archetype* archetype = entity_data->archetype;
    size_t entity_index = entity_data->index;

    struct NXS_ECS_ComponentPool* pool = _nxis_find_component_pool(archetype, type->id);
    if (!pool) {
        return false; //entity doesnt have component of type
    }

    memcpy(pool->data + (entity_index * pool->typesize), new_data, pool->typesize);

    return true;
}
inline bool NXS_ECS_HasComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity) {
    NXS_ASSERT(world);
    NXS_ASSERT(type);
    NXS_ASSERT(entity != 0);

    return (_nxis_find_component_pool(world->entities.data[entity].archetype, type->id) != NULL);
}
NXS_ECS_System* NXS_ECS_CreateSystem(NXS_ECS_World* world, NXS_ECS_SystemFunc function, NXS_ECS_SystemStage stage, NXS_ECS_Query* query) {
    NXS_ASSERT(world);
    NXS_ASSERT(query);

    uint32_t new_id;
    NXS_ECS_System* new_sys;

    switch(stage) {
        case NXS_ECS_SYSTEM_STAGE_INPUT:
            if (world->systems.input.free_count > 0) {
                new_id = world->systems.input.free_ids[--world->systems.input.free_count];
            } else {
                if (world->systems.input.free_count == 0 && world->systems.input.count >= world->systems.input.capacity) {
                    NXS_ECS_System* new = (NXS_ECS_System*)realloc(world->systems.input.systems, sizeof(NXS_ECS_System) * world->systems.input.capacity * 2);
                    if (!new) {
                        NXS_Error(strerror(errno));
                        return NULL;
                    }
                    world->systems.input.systems = new;
                    world->systems.input.capacity *= 2;
                }
                new_id = world->systems.input.count++;
            }
            new_sys = &world->systems.input.systems[new_id];
            break;
        case NXS_ECS_SYSTEM_STAGE_PROCESS:
            if (world->systems.proc.free_count > 0) {
                new_id = world->systems.proc.free_ids[--world->systems.proc.free_count];
            } else {
                if (world->systems.proc.free_count == 0 && world->systems.proc.count >= world->systems.proc.capacity) {
                    NXS_ECS_System* new = (NXS_ECS_System*)realloc(world->systems.proc.systems, sizeof(NXS_ECS_System) * world->systems.proc.capacity * 2);
                    if (!new) {
                        NXS_Error(strerror(errno));
                        return NULL;
                    }
                    world->systems.proc.systems = new;
                    world->systems.proc.capacity *= 2;
                }
                new_id = world->systems.proc.count++;
            }
            new_sys = &world->systems.proc.systems[new_id];
            break;
        case NXS_ECS_SYSTEM_STAGE_OUTPUT:
            if (world->systems.output.free_count > 0) {
                new_id = world->systems.output.free_ids[--world->systems.output.free_count];
            } else {
                if (world->systems.output.free_count == 0 && world->systems.output.count >= world->systems.output.capacity) {
                    NXS_ECS_System* new = (NXS_ECS_System*)realloc(world->systems.output.systems, sizeof(NXS_ECS_System) * world->systems.output.capacity * 2);
                    if (!new) {
                        NXS_Error(strerror(errno));
                        return NULL;
                    }
                    world->systems.output.systems = new;
                    world->systems.output.capacity *= 2;
                }
                new_id = world->systems.output.count++;
            }
            new_sys = &world->systems.output.systems[new_id];
            break;
        case NXS_ECS_SYSTEM_STAGE_MANUAL:
            //fall through
        default: //manual
            if (world->systems.manual.free_count > 0) {
                new_id = world->systems.manual.free_ids[--world->systems.manual.free_count];
            } else {
                if (world->systems.manual.free_count == 0 && world->systems.manual.count >= world->systems.manual.capacity) {
                    NXS_ECS_System* new = (NXS_ECS_System*)realloc(world->systems.manual.systems, sizeof(NXS_ECS_System) * world->systems.manual.capacity * 2);
                    if (!new) {
                        NXS_Error(strerror(errno));
                        return NULL;
                    }
                    world->systems.manual.systems = new;
                    world->systems.manual.capacity *= 2;
                }
                new_id = world->systems.manual.count++;
            }
            new_sys = &world->systems.manual.systems[new_id];
            break;
    }

    new_sys->id = new_id;
    new_sys->function = function;
    new_sys->query = query;
    new_sys->stage = stage;
    return new_sys;
}
void NXS_ECS_DestroySystem(NXS_ECS_World* world, NXS_ECS_System* sys) {
    NXS_ASSERT(world);
    NXS_ASSERT(sys);
    
    uint32_t removed_index;
    uint32_t last_index;
    uint32_t last_system_id;

    switch(sys->stage) {
        case NXS_ECS_SYSTEM_STAGE_INPUT:
            removed_index = sys->id;
            // Get the ID of the last system in the array
            last_index = world->systems.input.count - 1;
            last_system_id = world->systems.input.systems[last_index].id;
            // Perform a swap and pop if the system is not the last one
            if (removed_index != last_index) {
                // Move the last system to the removed system's position
                world->systems.input.systems[removed_index] = world->systems.input.systems[last_index];
                // Update the ID of the moved system
                world->systems.input.systems[removed_index].id = last_system_id;
            }
            // Return the system ID to the free list
            world->systems.input.free_ids[world->systems.input.free_count++] = removed_index;
            // Decrement the total system count for this stage
            world->systems.input.count--;
            break;
        case NXS_ECS_SYSTEM_STAGE_PROCESS:
            removed_index = sys->id;
            // Get the ID of the last system in the array
            last_index = world->systems.proc.count - 1;
            last_system_id = world->systems.proc.systems[last_index].id;
            // Perform a swap and pop if the system is not the last one
            if (removed_index != last_index) {
                // Move the last system to the removed system's position
                world->systems.proc.systems[removed_index] = world->systems.proc.systems[last_index];
                // Update the ID of the moved system
                world->systems.proc.systems[removed_index].id = last_system_id;
            }
            // Return the system ID to the free list
            world->systems.proc.free_ids[world->systems.proc.free_count++] = removed_index;
            // Decrement the total system count for this stage
            world->systems.proc.count--;
            break;
        case NXS_ECS_SYSTEM_STAGE_OUTPUT:
            removed_index = sys->id;
            // Get the ID of the last system in the array
            last_index = world->systems.output.count - 1;
            last_system_id = world->systems.output.systems[last_index].id;
            // Perform a swap and pop if the system is not the last one
            if (removed_index != last_index) {
                // Move the last system to the removed system's position
                world->systems.output.systems[removed_index] = world->systems.output.systems[last_index];
                // Update the ID of the moved system
                world->systems.output.systems[removed_index].id = last_system_id;
            }
            // Return the system ID to the free list
            world->systems.output.free_ids[world->systems.output.free_count++] = removed_index;
            // Decrement the total system count for this stage
            world->systems.output.count--;
            break;
        case NXS_ECS_SYSTEM_STAGE_MANUAL:
            //fall through
        default: //manual
            removed_index = sys->id;
            // Get the ID of the last system in the array
            last_index = world->systems.manual.count - 1;
            last_system_id = world->systems.manual.systems[last_index].id;
            // Perform a swap and pop if the system is not the last one
            if (removed_index != last_index) {
                // Move the last system to the removed system's position
                world->systems.manual.systems[removed_index] = world->systems.manual.systems[last_index];
                // Update the ID of the moved system
                world->systems.manual.systems[removed_index].id = last_system_id;
            }
            // Return the system ID to the free list
            world->systems.manual.free_ids[world->systems.manual.free_count++] = removed_index;
            // Decrement the total system count for this stage
            world->systems.manual.count--;
            break;
    }
    return;
}
bool NXS_ECS_RunSystem(NXS_ECS_World* world, NXS_ECS_System* sys) {
    NXS_ASSERT(world);
    NXS_ASSERT(sys);
    NXS_ASSERT(sys->query);
    NXS_ASSERT(sys->function);

    bool ret = true;

    //iterate through all archetypes that match this system's query.
    for (size_t i = 0; i < sys->query->arch_count; i++) {
        struct NXS_ECS_Archetype* arch = sys->query->archetypes[i];
        if (arch->count == 0) {
            continue;
        }

        //create stack-local array of pointers for the component data.
        void* component_data[sys->query->req_count];

        //map required types to the archetype component pools.
        size_t arch_pool_idx = 0;
        for (size_t j = 0; j < sys->query->req_count; j++) {
            uint32_t required_type_id = sys->query->req_types[j];

            //advance the archetype pointer until a match is found
            while (arch_pool_idx < arch->pool_count && arch->pools[arch_pool_idx].type_id < required_type_id) {
                arch_pool_idx++;
            }

            //check for a match
            if (arch_pool_idx < arch->pool_count && arch->pools[arch_pool_idx].type_id == required_type_id) {
                component_data[j] = arch->pools[arch_pool_idx].data;
                //optionally, advance the archetype pointer for the next search
                arch_pool_idx++;
            } else {
                //this should not happen if your query cache is up-to-date
                component_data[j] = NULL;
            }
        }

        ret &= sys->function(world, component_data, arch->count);
    }

    return ret;
}
inline NXS_ECS_System* NXS_ECS_GetInputSystemFromId(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    return &world->systems.input.systems[id];
}
inline NXS_ECS_System* NXS_ECS_GetProcessSystemFromId(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    return &world->systems.proc.systems[id];
}
inline NXS_ECS_System* NXS_ECS_GetOutputSystemFromId(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    return  &world->systems.output.systems[id];
}
inline NXS_ECS_System* NXS_ECS_GetManualSystemFromId(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    return  &world->systems.manual.systems[id];
}
inline uint32_t NXS_ECS_GetSystemId(NXS_ECS_System* sys) {
    NXS_ASSERT(sys);
    return sys->id;
}
inline NXS_ECS_SystemFunc NXS_ECS_GetSystemFunc(NXS_ECS_System* sys) {
    NXS_ASSERT(sys);
    return sys->function;
}
inline NXS_ECS_Query* NXS_ECS_GetSystemQuery(NXS_ECS_System* sys) {
    NXS_ASSERT(sys);
    return sys->query;
}
inline void NXS_ECS_SetSystemQuery(NXS_ECS_System* sys, NXS_ECS_Query* new) {
    NXS_ASSERT(sys);
    NXS_ASSERT(new);
    sys->query = new;
}
inline NXS_ECS_SystemStage NXS_ECS_GetSystemStage(NXS_ECS_System* sys) {
    NXS_ASSERT(sys);
    return sys->stage;
}
inline void NXS_ECS_SetSystemStage(NXS_ECS_World* world, NXS_ECS_System** sys, NXS_ECS_SystemStage new) {
    NXS_ASSERT(world);
    NXS_ASSERT(sys);

    //copy func & query
    NXS_ECS_Query* query = (*sys)->query;
    NXS_ECS_SystemFunc func = (*sys)->function;

    //remove system from old stage
    NXS_ECS_DestroySystem(world, *sys);

    //create 'new' system in other stage, with old data
    *sys = NXS_ECS_CreateSystem(world, func, new, query);
}
bool NXS_ECS_RunInputSystemStage(NXS_ECS_World* world) {
    NXS_ASSERT(world);

    bool ret = true;

    for (size_t i = 0; i < world->systems.input.count; i++) {
        if (!world->systems.input.systems[i].function) {
            continue; //not in use
        }
        ret &= NXS_ECS_RunSystem(world, &world->systems.input.systems[i]);
    }
    return ret;
}
bool NXS_ECS_RunProcessSystemStage(NXS_ECS_World* world) {
    NXS_ASSERT(world);

    bool ret = true;

    for (size_t i = 0; i < world->systems.proc.count; i++) {
        if (!world->systems.proc.systems[i].function) {
            continue; //not in use
        }
        ret &= NXS_ECS_RunSystem(world, &world->systems.proc.systems[i]);
    }
    return ret;
}
bool NXS_ECS_RunOutputSystemStage(NXS_ECS_World* world) {
    NXS_ASSERT(world);

    bool ret = true;

    for (size_t i = 0; i < world->systems.output.count; i++) {
        if (!world->systems.output.systems[i].function) {
            continue; //not in use
        }
        ret &= NXS_ECS_RunSystem(world, &world->systems.output.systems[i]);
    }
    return ret;
}
bool NXS_ECS_RunManualSystemStage(NXS_ECS_World* world, NXS_ECS_SystemStage stage) {
    NXS_ASSERT(world);

    bool ret = true;


    for (size_t i = 0; i < world->systems.manual.count; i++) {
        if (!world->systems.manual.systems[i].function || world->systems.manual.systems[i].stage != stage) {
            continue; //not in use
        }
        ret &= NXS_ECS_RunSystem(world, &world->systems.manual.systems[i]);
    }
    return ret;
}
NXS_ECS_Query* NXS_ECS_CreateQuery(NXS_ECS_World* world) {
    NXS_ASSERT(world);

    uint32_t new_id;

    if (world->queries.free_count > 0) {
        new_id = world->queries.free_ids[--world->queries.free_count];
    } else {
        if (world->queries.free_count == 0 && world->queries.count >= world->queries.capacity) {
            NXS_ECS_Query* new = (NXS_ECS_Query*)realloc(world->queries.queries, sizeof(NXS_ECS_Query) * world->queries.capacity * 2);
            if (!new) {
                NXS_Error(strerror(errno));
                return NULL;
            }
            world->queries.queries = new;
            world->queries.capacity *= 2;
        }
        new_id = world->queries.count++;
    }

    NXS_ECS_Query* new_query = &world->queries.queries[new_id];

    new_query->id = new_id;
    new_query->exc_count = 0;
    new_query->exc_types = NULL;
    new_query->req_count = 0;
    new_query->req_types = NULL;
    new_query->arch_count = 0;
    new_query->archetypes = NULL;
    return new_query;
}
void NXS_ECS_DestroyQuery(NXS_ECS_World* world, NXS_ECS_Query* query) {
    NXS_ASSERT(world);
    NXS_ASSERT(query);

    uint32_t removed_index = query->id;

    // Get the ID of the last system in the array
    uint32_t last_index = world->queries.count - 1;
    uint32_t last_system_id = world->queries.queries[last_index].id;

    // Perform a swap and pop if the system is not the last one
    if (removed_index != last_index) {
        // Move the last system to the removed system's position
        world->queries.queries[removed_index] = world->queries.queries[last_index];
        // Update the ID of the moved system
        world->queries.queries[removed_index].id = last_system_id;
    }

    // Return the system ID to the free list
    world->queries.free_ids[world->queries.free_count++] = removed_index;

    // Decrement the total system count for this stage
    world->queries.count--;
    return;
}
bool NXS_ECS_AddQueryComponent(NXS_ECS_World* world, NXS_ECS_Query* query, NXS_ECS_ComponentType* type, bool exclude) {
    NXS_ASSERT(world);
    NXS_ASSERT(query);
    NXS_ASSERT(type);

    size_t* count = (exclude) ? &query->exc_count : &query->req_count;
    uint32_t** array = (exclude) ? &query->exc_types : &query->req_types;

    //check if already present
    for (size_t i = 0; i < *count; i++) {
        if ((*array)[i] == type->id) {
            return false; //already present
        }
    }

    //realloc
    uint32_t* new = (uint32_t*)realloc((*array), sizeof(uint32_t) * ((*count)+1));
    if (!new) {
        NXS_Error(strerror(errno));
        return false;
    }
    (*array) = new;

    //assign
    (*array)[(*count)++] = type->id;

    return true;
}
bool NXS_ECS_RemoveQueryComponent(NXS_ECS_World* world, NXS_ECS_Query* query, NXS_ECS_ComponentType* type) {
    NXS_ASSERT(world);
    NXS_ASSERT(query);
    NXS_ASSERT(type);

    uint32_t** array_ptr = NULL;
    size_t* count_ptr = NULL;
    size_t removed_index = (size_t)-1;

    //check and assign if present
    for (size_t i = 0; i < query->req_count; i++) {
        if (query->req_types[i] == type->id) {
            array_ptr = &query->req_types;
            count_ptr = &query->req_count;
            removed_index = i;
            break;
        }
    }
    if (removed_index == (size_t)-1) {
        for (size_t i = 0; i < query->exc_count; i++) {
            if (query->exc_types[i] == type->id) {
                array_ptr = &query->exc_types;
                count_ptr = &query->exc_count;
                removed_index = i;
                break;
            }
        }
    }
    if (removed_index == (size_t)-1) {
        return false; //not present
    }

    size_t last_index = (*count_ptr) - 1;
    if (removed_index != last_index) {
        (*array_ptr)[removed_index] = (*array_ptr)[last_index];
    }

    (*count_ptr)--;
    
    //realloc
    if (*count_ptr == 0) {
        free(*array_ptr);
        *array_ptr = NULL;
    } else {
        uint32_t* new_array = (uint32_t*)realloc(*array_ptr, sizeof(uint32_t) * (*count_ptr));
        if (!new_array) {
            NXS_Error(strerror(errno));
            return false;
        }
        *array_ptr = new_array;
    }

    return true;
}
inline NXS_ECS_Query* NXS_ECS_GetQueryFromId(NXS_ECS_World* world, uint32_t id) {
    NXS_ASSERT(world);
    for (uint32_t i = 0; i < world->queries.count; i++) {
        if (world->queries.queries[i].id == id) {
            return &world->queries.queries[i];
        }
    }
    return NULL; //not found, might be in `free_ids`
}
inline uint32_t NXS_ECS_GetQueryId(NXS_ECS_Query* query) {
    NXS_ASSERT(query);
    return query->id;
}
void NXS_ECS_GetQuerryRequiredTypeList(NXS_ECS_Query* query, size_t* count, uint32_t* out) {
    NXS_ASSERT(query);
    NXS_ASSERT(count);
    
    if (!out) {
        *count = query->req_count;
        return;
    }
    memcpy(out, query->req_types, query->req_count);
    return;
}
void NXS_ECS_GetQuerryExcludeTypeList(NXS_ECS_Query* query, size_t* count, uint32_t* out) {
    NXS_ASSERT(query);
    NXS_ASSERT(out);
    
    if (!out) {
        *count = query->exc_count;
        return;
    }
    memcpy(out, query->exc_types, query->exc_count);
    return;
}
bool NXS_ECS_UpdateQuery(NXS_ECS_World* world, NXS_ECS_Query* query) {
    NXS_ASSERT(world);
    NXS_ASSERT(query);

    //free old cache
    if (query->archetypes) {
        free(query->archetypes);
    }
    
    //reset count and capacity
    query->archetypes = NULL;
    query->arch_count = 0;
    query->arch_capacity = 0;

    //iterate through all archetypes in world
    for (size_t i = 0; i < world->archetypes.count; ++i) {
        struct NXS_ECS_Archetype* current_arch = &world->archetypes.archetypes[i];

        if (_nxis_archetype_matches_query(current_arch, query)) {
            //check if the cache needs to be resized
            if (query->arch_count >= query->arch_capacity) {
                //determine new capacity (start with 4 if capacity is 0)
                size_t new_cap = query->arch_capacity == 0 ? 4 : query->arch_capacity * 2;
                
                //use realloc, if NULL, allocates
                struct NXS_ECS_Archetype** new_archetypes = (struct NXS_ECS_Archetype**)realloc(query->archetypes, new_cap * sizeof(struct NXS_ECS_Archetype*));
                if (!new_archetypes) {
                    NXS_Error(strerror(errno));
                    return false;
                }
                query->archetypes = new_archetypes;
                query->arch_capacity = new_cap;
            }
            // Add the matching archetype to the cache
            query->archetypes[query->arch_count++] = current_arch;
        }
    }
    return true;
}
bool NXS_ECS_UpdateQueries(NXS_ECS_World* world) {
    NXS_ASSERT(world);
    bool success = true;

    //iterate through all queries and update each one.
    for (size_t i = 0; i < world->queries.count; ++i) {
        if (!NXS_ECS_UpdateQuery(world, &world->queries.queries[i])) {
            success = false;
        }
    }

    return success;
}