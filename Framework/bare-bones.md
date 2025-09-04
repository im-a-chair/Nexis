# Bare Bones Nexis SDK structure

### The Nexis framework
The framework is devided up into a few different engines/libs:

when the game is launched the 'initial/main-scene' is loaded/run, it continues from there,
and whenever a scene is run:
    - he scene's dynamic lib is loaded to check its dependencies and contents
    - the necesairy (framework) libs are loaded
    - the assets used are loaded
    - scene contents are loaded
    - the scene's init func is run
    - all systems from the libs are run
    - the scene's proc func is run untill it returns false (should set the next scene)
    - the scene's quit func is run
    - things are freed, unloaded, etc...
    - next scene

- The Core lib, this hold the ECS code (Scenes should, aside from their list of entities, components, tags and systems also hold a list of assets), event system, basic hierarchy and transform system, libC integration, basic IO for e.g. saving and loading, the asset manager, threading and coroutines, time, deltatime, timers, and the utility 'lib'
    - ECS
        - ECS-World
            - Architypes
        - Entities
        - Components
            - Tags
        - Systems
        - Queries
    - Scenes
        - ECS-World (stores all entities, components, tags and architypes for that scene)
        - Systems list (list of pointers to all systems used in the scene)
        - Assets symbols list
        - engine lib list (list of libs (engine or extern) that are used in that scene, probably handled internally)
        - function pointers to the init, proc and quit functions for that scene
            - funcptr to scene entry/init function
            - funcptr to scene loop/proc/process function -- returns a `bool`, gets called over and over until it returns `false`
            - funcptr to scene exit/deinit/quit function
    - Events
        -  EventCallbacks (prob. component type, should have implementation for scripts)
    - Hierarchy & transform
    - Time, DeltaTime, FPS & Timers
    - Utility
        - Dynamic-Library handling, needed for the other libs
        - Threading & Coroutines/Concurrency
        - State/Config - Save/Load
        - Logging & Debugging

- The Windowing/Video/Display lib, this has components for windows, popups, message boxes, drag and drop, displaying image data on the screen, pixel-surface components, etc... (i.e. cpu rendering)

- The Input lib, which has basically all components and systems for taking info from the OS, though mainly input from external devices or simulated by the OS or even another application

- The Scripting lib (should also just have a function pointer component for native scripting), has components and systems for embedding Lua and using it for game scripting, also includes the Engine scripting API provided to the LuaVM to be used in scripts

- The Rendering lib, is made up of a few engines. These being:
    - a high-level 2D rendering engine that's backend agnostic (prob using SDL_renderer.h)
    - a lower-level rendering engine that uses the SDL3_GPU API to allow for more control while being backend agnostic

- The Physics lib,  a Box2D integration for 2D physics.

#### The Nexis API
The API also has some things of note mainly that it should, unlike the actual code (which is in C), have ports of both C and C++ and per language (though only the OOP ones) have, besides the main ECS API, a easier to use OOP API that still used the exact same Backend but abstracts the ECS away in just headers

### The nxis CLI
The CLI is also made up of a bunch of parts, mainly, like with the framework, a core though this time shell command and a set of utility software to be involved by said command, like the compilation systems, the core serializer, and more