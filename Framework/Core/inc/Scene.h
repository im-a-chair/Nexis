#ifndef _NXS_SCENE_H_
#define _NXS_SCENE_H_
#include "ECS.h"

/** TODO:
 * documantation
 * making `NXS_Asset` opaque
 * improving `NXS_GetData` and functions that use it
 * implement concurrency support (`Jobs.h`)
 */

/** General structure
 * load libs
 * - load lib from name
 * - resolve assets (might also be later)
 * - assign lib udata
 * - assign lib init, proc, quit funcptrs
 * 
 * create scene
 * - assign scene lib array
 * - assign scene udata
 * - assign scene init, proc and quit
 * 
 * run scene
 * - call scene's init function with ECS world address and udata
 *   - this init function should assign the ECS World, either making a new one or reusing an old one
 * - per lib, call init function with ECS world, scene data and lib udata
 *   - this one is to register systems, component, entities, etc. from the lib to the ECS world
 *   - this might also be used to resolve assets
 * 
 * - start loop
 *   - call input stage systems
 *   - call scene proc func
 *     - if a thing, call each lib proc func
 *   - call proc stage systems
 *   - call output stage systems
 *   - if scene proc func did not return false, repeat
 * 
 * - unload and choose next
 *   - call lib quit functions
 *   - call scene quit function, should return handle to next scene to run (NULL to quit the app)
 * 
 * unload
 * - unload and dealloc lib stuff
 * - unload and dealloc scene stuff
 * 
 * use scene handle from scene quit func to load next scene or quit
 * - scene quit func return should prob have been stored in a buffer to keep until after unload
 * 
 * example:
```C
#include "NexisCore.h"
#include "lib1.h"

typedef struct {
    NXS_ECS_ComponentType* position_type;
    NXS_ECS_ComponentType* veloctity_type;
    NXS_ECS_Entity entity;
    NXS_ECS_System* move_system;
} lib1_context;

bool lib1_init(NXS_Lib* lib, NXS_ECS_World* world, void* scene_udata) {
    lib1_context* lctx = (lib1_context*)lib->udata;

    //get addr & register

    //position comp type
    lctx->position_type = NXS_GetFunction(lib->handle, "RegisterPositionType")(world); //directly runs the function pointer, normally you'd probably save it in udata
    
    //velocity comp type
    lctx->velocity_type = NXS_GetFunction(lib->handle, "RegisterVelocityType")(world);
    
    //entity
    lctx->entity = NXS_GetFunction(lib->handle, "RegisterEntity")(world, lctx->position_type, lctx->velocity_type);

    //movement system
    lctx->move_system = NXS_GetFunction(lib->handle, "RegisterMovementSystem")(world);

    return true;
}
void lib1_quit(NXS_Lib* lib, NXS_ECS_World* world, void* scene_udata) {
    lib1_context* lctx = (lib1_context*)lib->udata;

    //unregister position
    NXS_ECS_DestroyComponentType(world, lctx->position_type);
    
    //unregister velocity
    NXS_ECS_DestroyComponentType(world, lctx->velocity_type);

    //unregister entity
    NXS_ECS_DestroyEntity(world, lctx->entity);

    //unregister move system
    NXS_ECS_DestroySystem(world, lctx->move_system);

    NXS_UnloadLib(lib->handle);
}
bool scene_init(NXS_Scene* scene) {
    scene->world = NXS_ECS_CreateWorld(10);
    if (!scene->world) {
        //error already reported by `NXS_ECS_CreateWorld`
        return false;
    }
    return true;
}
bool scene_proc(NXS_Scene* scene) {
    lib1_context* lctx = (lib1_context*)scene->libs[0]->udata;

    //if entity's x position is greater than 1000, quit
    lib1Position* position = (lib1Position*)NXS_ECS_GetComponentData(scene->world, lctx->position_type, lctx->entity);
    if (position->x > 1000) {
        NXS_Log("position reached boundry");
        return false;
    }

    return true;
}
NXS_Scene scene_quit(NXS_Scene* scene) {
    NXS_ECS_DestroyWorld(scene->world);
    return NULL; //dont run any scenes after
}

int main() {
    NXS_LogSetOutFile(stdout);

    lib1_context* lctx = (lib1_context*)calloc(1, sizeof(lib1_context));
    if (!lctx) {
        NXS_Error(strerror(errno));
        return 1;
    }

    NXS_Lib lib1 = {
        .handle = NXS_LoadLib("lib1"),
        .assets = NULL,
        .asset_count = 0,
        .udata = lctx,
        .init = lib1_init,
        .proc = NULL,
        .quit = lib1_quit
    };
    NXS_Scene scene = {
        .libs = &lib1,
        .lib_count = 1,
        .world = NULL,
        .udata = NULL,
        .init = scene_init,
        .proc = scene_proc,
        .quit = scene_quit
    };

    NXS_Scene* next_scene = &scene;
    while(next_scene) {
        next_scene = NXS_RunScene(next_scene);
    }

    free(lctx);
    return 0;
}
```
 */

/** NXS_LibHandle
 * TODO:
 */
typedef struct SDL_SharedObject NXS_LibHandle;

/** NXS_Asset
 * TODO:
 */
typedef struct NXS_Asset_T {
    const char* symbol_name;
    const unsigned char* start;
    const unsigned char* end;
    size_t size;
} NXS_Asset;

/** NXS_Lib
 * TODO:
 */
typedef struct NXS_Lib_T {
    NXS_LibHandle* handle;
    NXS_Asset* assets;
    size_t asset_count;
    bool (*init)(NXS_Lib* lib, NXS_ECS_World* world, void* scene_udata);
    bool (*proc)(NXS_Lib* lib, NXS_ECS_World* world, void* scene_udata);
    void (*quit)(NXS_Lib* lib, NXS_ECS_World* world, void* scene_udata);
    void* udata;
} NXS_Lib;

/** NXS_Scene
 * TODO:
 */
typedef struct NXS_Scene_T {
    NXS_Lib* libs;
    size_t lib_count;

    NXS_ECS_World* world;

    bool (*init)(NXS_Scene* scene); //should assign the ECS World, either making a new one or reusing an old one
    bool (*proc)(NXS_Scene* scene);
    NXS_Scene* (*quit)(NXS_Scene* scene);

    void* udata;
} NXS_Scene;


/** NXS_LoadLib
 * TODO:
 */
NXS_LibHandle* NXS_LoadLib(const char* path); //(from name, i.e. dlopen)

/** NXS_UnloadLib
 * TODO:
 */
#define NXS_UnloadLib(lib) SDL_UnloadObject((SDL_SharedObject*)lib)

/** NXS_GetAsset
 * TODO:
 */
NXS_Asset NXS_GetAsset(NXS_LibHandle* lib, const char* name); //from lib (to get start and end addr, from asset name)

/** NXS_GetFunction
 * TODO:
 */
#define NXS_GetFunction(lib, name) SDL_LoadFunction((NXS_LibHandle*)lib, name)

/** NXS_GetData
 * TODO:
 */
#define NXS_GetData(lib, name) (void*)SDL_LoadFunction((NXS_LibHandle*)lib, name)

/** NXS_RunScene
 * TODO:
 */
NXS_Scene* NXS_RunScene(NXS_Scene* scene); //(to do the whole ECS systems and funcptr speil for you)

#endif //_NXS_SCENE_H_