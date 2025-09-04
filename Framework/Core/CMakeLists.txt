# Framework/Core/CMakeLists.txt

# file(GLOB NxisCoreSource "./src/*.c" "./src/*/*.c")
set(NxisCoreSource
    src/Coroutines.c
    src/Disk.c
    src/ECS.c
    src/Encryption.c
    src/Events.c
    src/Log.c
    src/Math.c
    src/Scene.c
    src/SIMD.c
    src/Threads.c
    src/Time.c
    src/Types.c
    src/Components/ChildrenComponent.c
    src/Components/ParentComponent.c
    src/Components/TimerComponent.c
    src/Components/TransformComponent.c
    src/Systems/TimerSystem.c
    src/Systems/TransformSystem.c
)

# shared core library
add_library(CoreShared SHARED ${NxisCoreSource})
target_compile_options(CoreShared PRIVATE ${COMPILER_FLAGS})
target_include_directories(CoreShared PUBLIC "./inc")
target_link_libraries(CoreShared PUBLIC SDL3::SDL3)

# static lib
add_library(CoreStatic STATIC ${NxisCoreSource})
target_compile_options(CoreStatic PRIVATE ${COMPILER_FLAGS})
target_include_directories(CoreStatic PUBLIC "./inc")
target_link_libraries(CoreStatic PUBLIC SDL3::SDL3)

# installation rules
install(TARGETS CoreShared CoreStatic
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY "../inc" DESTINATION include/Nexis/Core)