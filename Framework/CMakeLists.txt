# Framework/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(NexisFramework LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${BUILD_TYPE})
endif()

# sys details
set(CMAKE_SYSTEM_PROCESSOR ${ARCHITECTURE})
set(CMAKE_SYSTEM_NAME ${PLATFORM})

# SDL3
find_package(SDL3 REQUIRED)

# sub-directories
add_subdirectory(Core/src)
# add_subdirectory(Display/src)
# add_subdirectory(Input/src)
# add_subdirectory(Scripting/src)
# add_subdirectory(Rendering/src)
# add_subdirectory(Physics/src)
# add_subdirectory(.../src)