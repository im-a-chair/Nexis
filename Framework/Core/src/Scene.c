#include "Scene.h"
#include "std.h"
#include "Log.h"
#include <SDL3/SDL.h>

NXS_LibHandle* NXS_LoadLib(const char* path) {
    NXS_ASSERT(path);

    //get file extension based on platform
    const char* extension = 
#if defined(SDL_PLATFORM_LINUX) || defined(SDL_PLATFORM_ANDROID) || \
    defined(SDL_PLATFORM_BSDI) || defined(SDL_PLATFORM_FREEBSD) || \
    defined(SDL_PLATFORM_NETBSD) || defined(SDL_PLATFORM_OPENBSD) || \
    defined(SDL_PLATFORM_EMSCRIPTEN) || defined(SDL_PLATFORM_HURD) || \
    defined(SDL_PLATFORM_IRIX) || defined(SDL_PLATFORM_QNXNTO) || \
    defined(SDL_PLATFORM_RISCOS) || defined(SDL_PLATFORM_SOLARIS) || \
    defined(SDL_PLATFORM_OSF) || defined(SDL_PLATFORM_HAIKU)
        ".so";
#elif defined(SDL_PLATFORM_WIN32) || defined(SDL_PLATFORM_WINDOWS) || \
    defined(SDL_PLATFORM_CYGWIN) || defined(SDL_PLATFORM_OS2)
        ".dll";
#elif defined(SDL_PLATFORM_3DS) || defined(SDL_PLATFORM_AIX)
        ".a";
#elif defined(SDL_PLATFORM_APPLE)
        ".dylib";
#elif defined(SDL_PLATFORM_HPUX)
        ".sl";
#elif defined(SDL_PLATFORM_PS2)
        ".irx";
#elif defined(SDL_PLATFORM_PSP)
        ".prx";
#elif defined(SDL_PLATFORM_VITA)
        ".suprx";
#endif

    size_t required_size = strlen(path) + strlen(extension) + 1;
    char* pathstr = (char*)malloc(required_size);
    if (!pathstr) {
        NXS_Error(strerror(errno));
        return NULL;
    }
    snprintf(pathstr, required_size, "%s%s", path, extension);
    SDL_SharedObject* lib = SDL_LoadObject(pathstr);
    free(pathstr); //to free regardless of success
    if (!lib) {
        NXS_Error(SDL_GetError());
    }
    return (NXS_LibHandle*)lib;
}
NXS_Asset NXS_GetAsset(NXS_LibHandle* lib, const char* name) {
    NXS_ASSERT(lib);
    NXS_ASSERT(name);
    NXS_Asset a = {0}; // error value

    // use fixed-size buffer to avoid dynamic allocation overhead
    char start_sym[256];
    char end_sym[256];
    char size_sym[256];

    NXS_ASSERT(strlen(name) + strlen("_binary__start") + 1 <= 256); //to avoid buffer overflows

    //create symbol names
    snprintf(start_sym, sizeof(start_sym), "_binary_%s_start", name);
    snprintf(end_sym, sizeof(end_sym), "_binary_%s_end", name);
    snprintf(size_sym, sizeof(size_sym), "_binary_%s_size", name);

    //get addresses
    a.start = (const unsigned char*)NXS_GetData(lib, start_sym);
    a.end = (const unsigned char*)NXS_GetData(lib, end_sym);
    size_t* size_ptr = (size_t*)NXS_GetData(lib, size_sym);

    if (!a.start || !a.end || !size_ptr) {
        NXS_Error(SDL_GetError());
        return a; //with error value
    }
    
    a.symbol_name = name;
    a.size = *size_ptr;

    return a;
}
NXS_Scene* NXS_RunScene(NXS_Scene* scene) {
    NXS_ASSERT(scene);

    //call scene's init function with ECS world address and udata
        //this init function should assign the ECS World, either making a new one or reusing an old one
    NXS_ASSERT(scene->init);
    if (!scene->init(scene)) {
        //init function is responsable for logging an error
        return NULL;
    }

    //per lib, call init function with ECS world, scene data and lib udata
        //this one is to register systems, component, entities, etc. from the lib to the ECS world
        //this might also be used to resolve assets
    for (size_t i = 0; i < scene->lib_count; i++) {
        NXS_ASSERT(scene->libs[i].init);
        if (!scene->libs[i].init(&scene->libs[i], scene->world, scene->udata)) {
            //init function is responsable for logging an error
            return NULL;
        }
    }

    //start loop
        //call input stage systems
        //call scene proc func
            //if a thing, call each lib proc func
        //call proc stage systems
        //call output stage systems
        //if scene proc func did not return false, repeat
    NXS_ASSERT(scene->proc);
    bool running = true;
    while(running) {
        //input stage
        if (!NXS_ECS_RunInputSystemStage(scene->world)) break;

        //proc
        if (!scene->proc(scene)) break;
        for (size_t i = 0; i < scene->lib_count; i++) {
            if (!scene->libs[i].proc) continue;
            if (!scene->libs[i].proc(&scene->libs[i], scene->world, scene->udata)) {
                running = false;
                break;
            }
        }
        if (!running) break;

        //proc stage
        if (!NXS_ECS_RunProcessSystemStage(scene->world)) break;

        //output stage
        if (!NXS_ECS_RunOutputSystemStage(scene->world)) break;
    }

    //unload and choose next
        //call lib quit functions
        //call scene quit function, should return handle to next scene to run (NULL to quit the app)
    for (size_t i = 0; i < scene->lib_count; i++) {
        NXS_ASSERT(scene->libs[i].quit);
        scene->libs[i].quit(&scene->libs[i], scene->world, scene->udata);
    }
    NXS_ASSERT(scene->quit);
    return scene->quit(scene);
}