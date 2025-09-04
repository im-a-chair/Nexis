# Framework/CMakeLists.txt

## TODO: add SIMD flags, for after implemented in `build.*`

cmake_minimum_required(VERSION 3.10)
project(NexisFramework LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "${BUILD_TYPE}")
endif()

# sys details
set(CMAKE_SYSTEM_PROCESSOR "${ARCHITECTURE}")
set(CMAKE_SYSTEM_NAME "${PLATFORM}")

# check compiler support
if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|MSVC")
    message(FATAL_ERROR "Compiler not supported.")
endif()

# set flags based on the CLI-provided OPTIMIZATION_LEVEL
set(COMPILER_FLAGS
    # default
    "$<$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>:-Wall;-Wextra>"
    "$<$<CMAKE_C_COMPILER_ID:MSVC>:/W4>"
    
    # -O0
    "$<$<AND:$<OPTIMIZATION_LEVEL:0>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-O0>"
    "$<$<AND:$<OPTIMIZATION_LEVEL:0>,$<CMAKE_C_COMPILER_ID:MSVC>>:/Od>"

    # -O1
    "$<$<AND:$<OPTIMIZATION_LEVEL:1>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-O1>"
    "$<$<AND:$<OPTIMIZATION_LEVEL:1>,$<CMAKE_C_COMPILER_ID:MSVC>>:/O1>"

    # -O2
    "$<$<AND:$<OPTIMIZATION_LEVEL:2>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-O2>"
    "$<$<AND:$<OPTIMIZATION_LEVEL:2>,$<CMAKE_C_COMPILER_ID:MSVC>>:/O2>"

    # -O3
    "$<$<AND:$<OPTIMIZATION_LEVEL:3>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-O3;-flto;-ffast-math>"
    "$<$<AND:$<OPTIMIZATION_LEVEL:3>,$<CMAKE_C_COMPILER_ID:MSVC>>:/O2;/Ox;/GL;/LTCG;/fp:fast>"

    # -O4 -- less stable (only makes difference with GNU/Clang)
    "$<$<AND:$<OPTIMIZATION_LEVEL:4>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-Os;-Ofast;-flto;-ffast-math>"
    "$<$<AND:$<OPTIMIZATION_LEVEL:4>,$<CMAKE_C_COMPILER_ID:MSVC>>:/O2;/Ox;/GL;/LTCG;/fp:fast>"

    # set march native if no arch provided
    "$<$<AND:$<CMAKE_BUILD_TYPE:Debug>,$<ARCHITECTURE:"">,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-march=native>)"

    # debug
    "$<$<AND:$<CMAKE_BUILD_TYPE:Debug>,$<OR:$<CMAKE_C_COMPILER_ID:GNU>,$<CMAKE_C_COMPILER_ID:Clang>>>:-g;-fsanitize=address>"
    "$<$<AND:$<CMAKE_BUILD_TYPE:Debug>,$<CMAKE_C_COMPILER_ID:MSVC>>:/Zi;/RTC1;/MTd;/MDd>"

    # maybe add at a later point, when C++ usage more known/certain
    # release
    # $<$<AND:$<CMAKE_BUILD_TYPE:"Release">, $<OR:$<CMAKE_C_COMPILER_ID:"GNU">,$<CMAKE_C_COMPILER_ID:"Clang">>>:"-fno-rtti">
    # $<$<AND:$<CMAKE_BUILD_TYPE:"Release">, $<OR:$<CMAKE_C_COMPILER_ID:"GNU">,$<CMAKE_C_COMPILER_ID:"Clang">>>:"-fno-exceptions">
)
add_compile_definitions(
    # Compiler-specific defines
    $<$<CMAKE_C_COMPILER_ID:GNU>:NXS_GCC>
    $<$<CMAKE_C_COMPILER_ID:Clang>:NXS_CLANG>
    $<$<CMAKE_C_COMPILER_ID:MSVC>:NXS_MSVC>

    # Build type defines
    $<$<CONFIG:Debug>:NXS_DEBUG>
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NXS_RELEASE>
    $<$<CONFIG:Release>:NDEBUG>

    # Processor architecture defines
    $<$<OR:$<CMAKE_SYSTEM_PROCESSOR:x86>,$<CMAKE_SYSTEM_PROCESSOR:i386>>:DNXS_X86>
    $<$<OR:$<CMAKE_SYSTEM_PROCESSOR:x86_64>,$<CMAKE_SYSTEM_PROCESSOR:x64>,$<CMAKE_SYSTEM_PROCESSOR:i686>>:DNXS_X64>
    $<$<OR:$<CMAKE_SYSTEM_PROCESSOR:arm>,$<CMAKE_SYSTEM_PROCESSOR:arm32>>:DNXS_AMR32>
    $<$<OR:$<CMAKE_SYSTEM_PROCESSOR:arm64>,$<CMAKE_SYSTEM_PROCESSOR:aarch>,$<CMAKE_SYSTEM_PROCESSOR:aarch64>>:NXS_ARM64>
)

# SDL3
find_package(SDL3 REQUIRED)

# sub-directories
add_subdirectory(Core)
# add_subdirectory(Display)
# add_subdirectory(Input)
# add_subdirectory(Scripting)
# add_subdirectory(Rendering)
# add_subdirectory(Physics)
# add_subdirectory(...)