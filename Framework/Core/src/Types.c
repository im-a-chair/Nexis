#include "Types.h"
#include "Log.h"
#include "std.h"

///TODO: replace pointer checks with asserts

// ----- Dynamic Array -----

struct NXS_DynamicArray_T {
    void* data;
    size_t typesize; //in bytes
    size_t capacity;
    size_t count;
    size_t start_index; //for poll itteration
};
void _NXS_AllignDynarrStartIndex(NXS_DynamicArray* da) {
    if (da->count > 0 && da->start_index != 0) {
        // move from the start_index to the beginning of the array
        memmove(da->data, // Destination: start of the array
                da->data + (da->start_index * da->typesize), // Source: the first active element
                da->count * da->typesize); // Size: the total size of active elements
        da->start_index = 0;
    }
}
NXS_DynamicArray* NXS_CreateDynamicArray(size_t typesize, size_t init_cap) {
    NXS_ASSERT(typesize != 0);
    NXS_ASSERT(init_cap != 0);
    NXS_DynamicArray* new = (NXS_DynamicArray*)calloc(1, sizeof(NXS_DynamicArray));
    if (!new) {
        NXS_Error("Failed to allocate new `NXS_DynamicArray` in `NXS_CreateDynamicArray`");
        return NULL;
    }
    new->data = calloc(init_cap, typesize);
    if (!new->data) {
        NXS_Error("Failed to allocate internal array in `NXS_CreateDynamicArray`");
        return NULL;
    }
    new->capacity = init_cap;
    new->typesize = typesize;
    new->count = 0;
    new->start_index = 0;
    return new;
}
void NXS_DestroyDynamicArray(NXS_DynamicArray* dynarr) {
    if (dynarr) {
        if (dynarr->data) {
            free(dynarr->data);
        }
        free(dynarr);
    }
}
bool NXS_DynamicArrayPush(NXS_DynamicArray* dynarr, void* data) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(data);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    if (dynarr->count >= dynarr->capacity) {
        void* new = realloc(dynarr->data, dynarr->capacity * dynarr->typesize * 2);
        if (!new) {
            NXS_Error("Failed to reallocate internal array in `NXS_DynamicArrayPush`");
            return false;
        }
        dynarr->data = new;
        dynarr->capacity *= 2;
    }
    if (!memcpy(dynarr->data + (dynarr->count * dynarr->typesize), data, dynarr->typesize)) {
        NXS_Error("`memcpy` failed in `NXS_DynamicArrayPush`");
        return false;
    }
    dynarr->count++;
    return true;
}
bool NXS_DynamicArrayPop(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    memset(dynarr->data + ((dynarr->count - 1) * dynarr->typesize), 0, dynarr->typesize);
    dynarr->count--;
    return true;
}
bool NXS_DynamicArrayInsert(NXS_DynamicArray* dynarr, size_t index, void* data) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(data);
    NXS_ASSERT(dynarr->data);
    NXS_ASSERT(index > dynarr->count);
    _NXS_AllignDynarrStartIndex(dynarr);
    if (dynarr->count >= dynarr->capacity) {
        void* new = realloc(dynarr->data, dynarr->capacity * dynarr->typesize * 2);
        if (!new) {
            NXS_Error("Failed to reallocate internal array in `NXS_DynamicArrayInsert`");
            return false;
        }
        dynarr->data = new;
        dynarr->capacity *= 2;
    }
    //shift all up by one, starting at `index`
    memmove(dynarr->data + ((index + 1) * dynarr->typesize),
            dynarr->data + (index * dynarr->typesize),
            (dynarr->count - index) * dynarr->typesize);
    //assign
    memcpy(dynarr->data + (index * dynarr->typesize), data, dynarr->typesize);
    dynarr->count++;
    return true;
}
bool NXS_DynamicArrayRemove(NXS_DynamicArray* dynarr, size_t index) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    NXS_ASSERT(index > dynarr->count);
    if (index < dynarr->count - 1) {
        memmove(dynarr->data + (index * dynarr->typesize),
                dynarr->data + ((index + 1) * dynarr->typesize),
                (dynarr->count - 1 - index) * dynarr->typesize);
    }
    dynarr->count--;
    return true;
}
void* NXS_DynamicArrayIndex(NXS_DynamicArray* dynarr, size_t index) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    NXS_ASSERT(index > dynarr->count);
    _NXS_AllignDynarrStartIndex(dynarr);
    return dynarr->data + (index * dynarr->typesize);
}
size_t NXS_DynamicArrayFind(NXS_DynamicArray* dynarr, void* data) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(data);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    for (int i = 0; i < dynarr->count; i++) {
        if (memcmp(dynarr->data + (i * dynarr->typesize), data, dynarr->typesize) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}
size_t NXS_DynamicArraySize(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    return dynarr->capacity;
}
size_t NXS_DynamicArrayCount(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    return dynarr->count;
}
size_t NXS_DynamicArrayTypeSize(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    return dynarr->typesize;
}
bool NXS_DynamicArrayClear(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    for (int i = 0; i < dynarr->count; i++) {
        memset(dynarr->data + (i * dynarr->typesize), 0, dynarr->typesize);
    }
    return true;
}
void NXS_DynamicArraySort(NXS_DynamicArray* dynarr, __compar_fn_t compfunc) {
    qsort(dynarr->data, dynarr->count, dynarr->typesize, compfunc);
}
int NXS_DynamicArrayStdCompFunc8(const void* a, const void* b) {
    //-n = a, then b
    //0 = a == b
    //n = b, then a
    return (int)((*(uint8_t*)a) - (*(uint8_t*)b));
}
int NXS_DynamicArrayStdCompFunc16(const void* a, const void* b) {
    //-n = a, then b
    //0 = a == b
    //n = b, then a
    return (int)((*(uint16_t*)a) - (*(uint16_t*)b));
}
int NXS_DynamicArrayStdCompFunc32(const void* a, const void* b) {
    //-n = a, then b
    //0 = a == b
    //n = b, then a
    return (int)((*(uint32_t*)a) - (*(uint32_t*)b));
}
int NXS_DynamicArrayStdCompFunc64(const void* a, const void* b) {
    //-n = a, then b
    //0 = a == b
    //n = b, then a
    if ((*(uint64_t*)a) < (*(uint64_t*)b)) { //a < b
        return -1;
    } else if ((*(uint64_t*)a) > (*(uint64_t*)b)) { //a > b
        return 1;
    }
    return 0; // a == b
}
bool NXS_DynamicArrayResize(NXS_DynamicArray* dynarr, size_t new_size) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    if (new_size == dynarr->capacity) {
        return true; //dont resize, nothing to be done
    }
    void* new = realloc(dynarr->data, new_size * dynarr->typesize);
    if (!new) {
        NXS_Error("Failed to reallocate internal array in `NXS_DynamicArrayResize`");
        return false;
    }
    dynarr->data = new;
    dynarr->capacity = new_size;
    if (dynarr->count > new_size) {
        dynarr->count = new_size;
    }
    return true;
}
bool NXS_DynamicArrayReserve(NXS_DynamicArray* dynarr, size_t space_count) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(dynarr->data);
    _NXS_AllignDynarrStartIndex(dynarr);
    void* new = realloc(dynarr->data, (dynarr->capacity + space_count) * dynarr->typesize);
    if (!new) {
        NXS_Error("Failed to reallocate internal array in `NXS_DynamicArrayReserve`");
        return false;
    }
    dynarr->data = new;
    dynarr->capacity += space_count;
    return true;
}
bool NXS_DynamicArrayEmpty(NXS_DynamicArray* dynarr) {
    NXS_ASSERT(dynarr);
    return (dynarr->count < 1);
}
bool NXS_DynamicArrayPoll(NXS_DynamicArray* dynarr, void* out) {
    NXS_ASSERT(dynarr);
    NXS_ASSERT(out);
    NXS_ASSERT(dynarr->data);
    if (NXS_DynamicArrayEmpty(dynarr)) {
        dynarr->start_index = 0;
        return false;
    }
    memcpy(out, dynarr->data + (dynarr->start_index * dynarr->typesize), dynarr->typesize);
    dynarr->start_index++;
    dynarr->count--;
    return true;
}

// ----- Hash Map -----
struct _NXS_HashNode {
    size_t key;
    void* value;
    size_t value_size;
    struct _NXS_HashNode* next;
};
struct NXS_HashMap_T {
    NXS_DynamicArray* buckets; //array of nodes
    size_t node_count; //not bucket count
};
size_t _NXS_Hash(NXS_HashMap* map, size_t key) {
    return key % map->buckets->capacity;
}
NXS_HashMap* NXS_CreateHashMap(size_t init_cap) {
    NXS_ASSERT(init_cap != 0);
    NXS_HashMap* map = malloc(sizeof(NXS_HashMap));
    if (!map) {
        NXS_Error("Failed to allocate new `NXS_HashMap` in `NXS_CreateHashMap`");
        return NULL;
    }
    map->buckets = NXS_CreateDynamicArray(sizeof(struct _NXS_HashNode*), init_cap);
    if (!map->buckets->data) {
        NXS_Error("Failed to allocate internal array in `NXS_CreateHashMap`");
        free(map);
        return NULL;
    }
    map->node_count = 0;
    return map;
}
void NXS_DestroyHashMap(NXS_HashMap* map) {
    if (map) {
        if (map->buckets) {
            for (size_t i = 0; i < NXS_DynamicArraySize(map->buckets); ++i) {
                struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, i);
                struct _NXS_HashNode* current = *head_ptr;
                while (current) {
                    struct _NXS_HashNode* temp = current;
                    current = current->next;
                    free(temp->value); // Free the user's data
                    free(temp); // Free the node
                }
            }
            NXS_DestroyDynamicArray(map->buckets);
        }
        free(map);
    }
}
bool NXS_HashMapInsert(NXS_HashMap* map, size_t key, void* value, size_t typesize) {
    NXS_ASSERT(map);

    // Check if the key already exists
    if (NXS_HashMapContains(map, key)) {
        return false;
    }
    
    // Check load factor and resize if needed
    if (map->node_count >= map->buckets->capacity * 0.75) {
        NXS_DynamicArrayResize(map->buckets, map->buckets->capacity * 2);
    }
    
    size_t index = _NXS_Hash(map, key);
    struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, index);

    // Create and initialize the new node
    struct _NXS_HashNode* newNode = malloc(sizeof(struct _NXS_HashNode));
    if (!newNode) {
        NXS_Error("Failed to allocate new node in `NXS_HashMapInsert`");
        return false;
    }
    
    newNode->key = key;
    newNode->value = malloc(typesize);
    if (!newNode->value) {
        NXS_Error("Failed to allocate new node value in `NXS_HashMapInsert`");
        free(newNode);
        return false;
    }
    memcpy(newNode->value, value, typesize);
    newNode->value_size = typesize;
    
    // Prepend the new node to the linked list
    newNode->next = *head_ptr;
    NXS_DynamicArraySet(map->buckets, index, &newNode);
    
    map->node_count++;
    return true;
}
size_t NXS_HashMapGet(NXS_HashMap* map, size_t key, void* out) {
    NXS_ASSERT(map);
    NXS_ASSERT(out);

    size_t index = _NXS_Hash(map, key);
    struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, index);
    
    struct _NXS_HashNode* current = *head_ptr;
    while (current) {
        if (current->key == key) {
            memcpy(out, current->value, current->value_size);
            return current->value_size;
        }
        current = current->next;
    }
    return 0; // Key not found
}
bool NXS_HashMapSet(NXS_HashMap* map, size_t key, void* value) {
    NXS_ASSERT(map);

    size_t index = _NXS_Hash(map, key);
    struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, index);
    
    struct _NXS_HashNode* current = *head_ptr;
    while (current) {
        if (current->key == key) {
            // Update the value
            current->value = realloc(current->value, current->value_size);
            if (current->value == NULL) {
                NXS_Error("Failed to realloc node value in `NXS_HashMapSet`");
                return false;
            }
            memcpy(current->value, value, current->value_size);
            return true;
        }
        current = current->next;
    }
    return false; // Key not found
}
bool NXS_HashMapRemove(NXS_HashMap* map, size_t key) {
    NXS_ASSERT(map);

    size_t index = _NXS_Hash(map, key);
    struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, index);
    
    struct _NXS_HashNode* current = *head_ptr;
    struct _NXS_HashNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) { // Removing the head of the list
                *head_ptr = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->value);
            free(current);
            map->node_count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false; // Key not found
}
bool NXS_HashMapContains(NXS_HashMap* map, size_t key) {
    NXS_ASSERT(map);

    size_t index = _NXS_Hash(map, key);
    struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, index);
    
    struct _NXS_HashNode* current = *head_ptr;
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool NXS_HashMapFind(NXS_HashMap* map, void* value, size_t typesize) {
    NXS_ASSERT(map);
    for (size_t i = 0; i < NXS_DynamicArraySize(map->buckets); ++i) {
        struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, i);
        struct _NXS_HashNode* current = *head_ptr;
        while (current) {
            if (current->value_size == typesize && memcmp(current->value, value, typesize) == 0) {
                return true;
            }
            current = current->next;
        }
    }
    return false;
}
size_t NXS_HashMapSize(NXS_HashMap* map) {
    NXS_ASSERT(map);
    return map->node_count;
}
bool NXS_HashMapClear(NXS_HashMap* map) {
    NXS_ASSERT(map);

    for (size_t i = 0; i < NXS_DynamicArraySize(map->buckets); ++i) {
        struct _NXS_HashNode** head_ptr = (struct _NXS_HashNode**)NXS_DynamicArrayIndex(map->buckets, i);
        struct _NXS_HashNode* current = *head_ptr;
        while (current != NULL) {
            struct _NXS_HashNode* temp = current;
            current = current->next;
            free(temp->value);
            free(temp);
        }
        // Set the bucket pointer to NULL
        void* null_ptr = NULL;
        NXS_DynamicArraySet(map->buckets, i, &null_ptr);
    }
    map->node_count = 0;
    return true;
}

// ----- Quad Tree -----
//Type
//Functions

// ----- Oct Tree -----
//Type
//Functions

// ----- Heap (Tree) -----
//Type
//Functions

// ----- Graph -----
//Type
//Functions
