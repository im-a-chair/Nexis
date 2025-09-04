#ifndef _NXS_ECS_H_
#define _NXS_ECS_H_
#include "std.h"

/** ECS.h
 * 'memory contract':
 * this lib will only allocate data that is directly returned by a function (mostly only aplies to Create- functions)
 */

/// ----- Types -----

/** NXS_ECS_World
 * is an opaque type of a struct that internally stores and keeps track of all
 * entities, component types, tags, components and tag instances
 * of a single context (which is what the `NXS_ECS_World` is, a context).
 */
typedef struct NXS_ECS_World_T NXS_ECS_World;

/** NXS_ECS_Entity
 * is a `uint32_t` id, used to index a set of components,
 * like the entity itself,
 * stored at a `NXS_ECS_World` through functions.
 * \warning 'making' a ECS entity DOES require allocations,
 * \warning do not 'just choose' a number, nor 'just use the next number'.
 * \warning similarly, it DOES require deallocations, so REMEMBER TO FREE IT with `NXS_DestroyEntity`.
 */
typedef uint32_t NXS_ECS_Entity;

/** NXS_ECS_ComponentType
 * is an opaque type that internally stores data about a struct (mostly it's size),
 * to be used to add instences to an entity.
 */
typedef struct NXS_ECS_ComponentType_T NXS_ECS_ComponentType;

/** NXS_ECS_Constructor
 * is a function pointer used for registering the function
 * to run upon adding a component instance to an entity
 */
typedef bool (*NXS_ECS_Constructor)(NXS_ECS_World* world, NXS_ECS_Entity entity, NXS_ECS_ComponentType* type, void* component);

/** NXS_ECS_Destructor
 * is a function pointer used for registering the function
 * to run upon removing a component instance from an entity
 */
typedef bool (*NXS_ECS_Destructor)(NXS_ECS_World* world, NXS_ECS_Entity entity, NXS_ECS_ComponentType* type, void* component);

/** NXS_ECS_SystemStage
 * TODO:
 */
typedef enum NXS_ECS_SystemStage {
    NXS_ECS_SYSTEM_STAGE_INPUT, //for systems that read extern data, and write local data
    NXS_ECS_SYSTEM_STAGE_PROCESS, //for systems that read and write local data
    NXS_ECS_SYSTEM_STAGE_OUTPUT, //for systems that read local data, and write extern data
    NXS_ECS_SYSTEM_STAGE_MANUAL //for systems that shouldnt be automatically called
    //anything higher will also be manual, for custom staging
} NXS_ECS_SystemStage;

/** NXS_System
 * is a function pointer used as a signature for ECS Systems,
 * which are functions that querry all entities that fit
 * a given signature (set of component(s) and tag(s) or architype),
 * so they can be registered in a `NXS_Scene`.
 * \note will probably get a priority system
 * \note and concurrency implementation in the future,
 * \note for now the order is based on the order in the array in the scene.
 */
typedef bool (*NXS_ECS_SystemFunc)(NXS_ECS_World* world, void* component_data[], size_t entity_count);

/** NXS_ECS_System
 * TODO:
 */
typedef struct NXS_ECS_System_T NXS_ECS_System;

/** NXS_ECS_Query
 * is a structure that holds a set of component types to use
 * in querrying entities that athere to a certain signature (archetype).
 * it has two lists, one with all required component types, and one with
 * all component types to exclude (that the queried entities should not have).
 * all component types are stored per id.
 * 
 * \note to access the query result, register a system with
 * `NXS_ECS_SYSTEM_STAGE_MANUAL`and the query you want to access
 */
typedef struct NXS_ECS_Query_T NXS_ECS_Query;

/// ----- Functions -----


/** NXS_ECS_CreateWorld
 * TODO:
 */
NXS_ECS_World* NXS_ECS_CreateWorld(size_t init_cap);

/** NXS_ECS_DestroyWorld
 * TODO:
 */
void NXS_ECS_DestroyWorld(NXS_ECS_World* world);

/** NXS_ECS_GetEntityCount
 * TODO:
 */
inline uint32_t NXS_ECS_GetEntityCount(NXS_ECS_World* world);

/** NXS_ECS_GetComponentTypeCount
 * TODO:
 */
inline uint32_t NXS_ECS_GetComponentTypeCount(NXS_ECS_World* world);

/** NXS_ECS_GetArchetypeCount
 * TODO:
 */
inline uint32_t NXS_ECS_GetArchetypeCount(NXS_ECS_World* world);

/** NXS_ECS_GetQueryCount
 * TODO:
 */
inline uint32_t NXS_ECS_GetQueryCount(NXS_ECS_World* world);

/** NXS_ECS_GetSystemCount
 * TODO:
 */
inline uint32_t NXS_ECS_GetSystemCount(NXS_ECS_World* world);

/** NXS_ECS_CreateEntity
 * TODO:
 */
NXS_ECS_Entity NXS_ECS_CreateEntity(NXS_ECS_World* world); //less efficient, more dynamic (only on creation, after that same flexibility and effieciency)

/** NXS_ECS_CreateEntityWithComponents
 * TODO:
 */
NXS_ECS_Entity NXS_ECS_CreateEntityWithComponents(NXS_ECS_World* world, NXS_ECS_ComponentType* types[], size_t type_count); //less dynamic, more efficient (only on creation, after that same flexibility and effieciency)

/** NXS_ECS_DestroyEntity
 * TODO:
 */
void NXS_ECS_DestroyEntity(NXS_ECS_World* world, NXS_ECS_Entity entity);

/** NXS_ECS_CreateComponentType
 * TODO:
 */
NXS_ECS_ComponentType* NXS_ECS_CreateComponentType(NXS_ECS_World* world, const char* name, size_t size, NXS_ECS_Constructor constructor, NXS_ECS_Destructor destructor); //if `size` is 0 its a tag

/** NXS_ECS_DestroyComponentType
 * TODO:
 */
void NXS_ECS_DestroyComponentType(NXS_ECS_World* world, NXS_ECS_ComponentType* type);

/** NXS_ECS_GetComponentTypeName
 * TODO:
 */
inline const char* NXS_ECS_GetComponentTypeName(NXS_ECS_ComponentType* type);

/** NXS_ECS_GetComponentTypeId
 * TODO:
 */
inline uint32_t NXS_ECS_GetComponentTypeId(NXS_ECS_ComponentType* type);

/** NXS_ECS_GetComponentTypeSize
 * TODO:
 */
inline size_t NXS_ECS_GetComponentTypeSize(NXS_ECS_ComponentType* type);

/** NXS_ECS_GetComponentTypeByName
 * TODO:
 */
NXS_ECS_ComponentType* NXS_ECS_GetComponentTypeByName(NXS_ECS_World* world, const char* name);

/** NXS_ECS_GetComponentTypeById
 * TODO:
 */
inline NXS_ECS_ComponentType* NXS_ECS_GetComponentTypeById(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_SetConstructor
 * TODO:
 */
inline void NXS_ECS_SetConstructor(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Constructor constructor); //set to NULL to remove

/** NXS_ECS_SetDestructor
 * TODO:
 */
inline void NXS_ECS_SetDestructor(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Destructor destructor); //set to NULL to remove

/** NXS_ECS_AddComponent
 * TODO:
 */
bool NXS_ECS_AddComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, void* initial_data, bool ignore_constructor); // use command buffer to more efficiently change entity archetype

/** NXS_ECS_RemoveComponent
 * TODO:
 */
bool NXS_ECS_RemoveComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, bool ignore_destructor);

/** NXS_ECS_GetComponentData
 * TODO:
 */
inline const void* NXS_ECS_GetComponentData(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity);

/** NXS_SetComponentData
 * TODO:
 */
inline bool NXS_SetComponentData(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity, void* new_data);

/** NXS_ECS_HasComponent
 * TODO:
 */
inline bool NXS_ECS_HasComponent(NXS_ECS_World* world, NXS_ECS_ComponentType* type, NXS_ECS_Entity entity);

/** NXS_ECS_CreateSystem
 * TODO:
 */
NXS_ECS_System* NXS_ECS_CreateSystem(NXS_ECS_World* world, NXS_ECS_SystemFunc function, NXS_ECS_SystemStage stage, NXS_ECS_Query* query);

/** NXS_ECS_DestroySystem
 * TODO:
 */
void NXS_ECS_DestroySystem(NXS_ECS_World* world, NXS_ECS_System* sys);

/** NXS_ECS_RunSystem
 * TODO:
 */
bool NXS_ECS_RunSystem(NXS_ECS_World* world, NXS_ECS_System* sys);

/** NXS_ECS_GetInputSystemFromId
 * TODO:
 */
inline NXS_ECS_System* NXS_ECS_GetInputSystemFromId(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_GetProcessSystemFromId
 * TODO:
 */
inline NXS_ECS_System* NXS_ECS_GetProcessSystemFromId(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_GetOutputSystemFromId
 * TODO:
 */
inline NXS_ECS_System* NXS_ECS_GetOutputSystemFromId(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_GetManualSystemFromId
 * TODO:
 */
inline NXS_ECS_System* NXS_ECS_GetManualSystemFromId(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_GetSystemId
 * TODO:
 */
inline uint32_t NXS_ECS_GetSystemId(NXS_ECS_System* sys);

/** NXS_ECS_GetSystemFunc
 * TODO:
 */
inline NXS_ECS_SystemFunc NXS_ECS_GetSystemFunc(NXS_ECS_System* sys);

/** NXS_ECS_GetSystemQuery
 * TODO:
 */
inline NXS_ECS_Query* NXS_ECS_GetSystemQuery(NXS_ECS_System* sys);

/** NXS_ECS_SetSystemQuery
 * TODO:
 */
inline void NXS_ECS_SetSystemQuery(NXS_ECS_System* sys, NXS_ECS_Query* new);

/** NXS_ECS_GetSystemStage
 * TODO:
 */
inline NXS_ECS_SystemStage NXS_ECS_GetSystemStage(NXS_ECS_System* sys);

/** NXS_ECS_SetSystemStage
 * TODO:
 */
inline void NXS_ECS_SetSystemStage(NXS_ECS_World* world, NXS_ECS_System** sys, NXS_ECS_SystemStage new); //not very efficient

/** NXS_ECS_RunInputSystemStage
 * TODO:
 */
bool NXS_ECS_RunInputSystemStage(NXS_ECS_World* world);

/** NXS_ECS_RunProcessSystemStage
 * TODO:
 */
bool NXS_ECS_RunProcessSystemStage(NXS_ECS_World* world);

/** NXS_ECS_RunOutputSystemStage
 * TODO:
 */
bool NXS_ECS_RunOutputSystemStage(NXS_ECS_World* world);

/** NXS_ECS_RunManualSystemStage
 * TODO:
 */
bool NXS_ECS_RunManualSystemStage(NXS_ECS_World* world, NXS_ECS_SystemStage stage); //for running custom stages, i.e. `stage >= NXS_ECS_SYSTEM_STAGE_MANUAL`

/** NXS_ECS_CreateQuery
 * TODO:
 */
NXS_ECS_Query* NXS_ECS_CreateQuery(NXS_ECS_World* world);

/** NXS_ECS_DestroyQuery
 * TODO:
 */
void NXS_ECS_DestroyQuery(NXS_ECS_World* world, NXS_ECS_Query* query);

/** NXS_ECS_AddQueryComponent
 * TODO:
 */
bool NXS_ECS_AddQueryComponent(NXS_ECS_World* world, NXS_ECS_Query* query, NXS_ECS_ComponentType* type, bool exclude);

/** NXS_ECS_RemoveQueryComponent
 * TODO:
 */
bool NXS_ECS_RemoveQueryComponent(NXS_ECS_World* world, NXS_ECS_Query* query, NXS_ECS_ComponentType* type);

/** NXS_ECS_GetQueryFromId
 * TODO:
 */
inline NXS_ECS_Query* NXS_ECS_GetQueryFromId(NXS_ECS_World* world, uint32_t id);

/** NXS_ECS_GetQueryId
 * TODO:
 */
inline uint32_t NXS_ECS_GetQueryId(NXS_ECS_Query* query);

/** NXS_ECS_GetQuerryRequiredTypeList
 * TODO:
 */
void NXS_ECS_GetQuerryRequiredTypeList(NXS_ECS_Query* query, size_t* count, uint32_t* out);

/** NXS_ECS_GetQuerryExcludeTypeList
 * TODO:
 */
void NXS_ECS_GetQuerryExcludeTypeList(NXS_ECS_Query* query, size_t* count, uint32_t* out);

/** NXS_ECS_UpdateQuery
 * TODO:
 */
bool NXS_ECS_UpdateQuery(NXS_ECS_World* world, NXS_ECS_Query* query);

/** NXS_ECS_UpdateQueries
 * TODO:
 */
bool NXS_ECS_UpdateQueries(NXS_ECS_World* world);

#endif //_NXS_ECS_H_