# Framework/Core/src/CMakeLists.txt

file(GLOB NxisCoreSource "./*.c" "./*/*.c")

# set flags based on the CLI-provided OPTIMIZATION_LEVEL
# if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
#     set(COMPILER_FLAGS "")
#     if(OPTIMIZATION_LEVEL STREQUAL "0")
#         set(COMPILER_FLAGS "-O0")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "1")
#         set(COMPILER_FLAGS "-O1")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "2")
#         set(COMPILER_FLAGS "-O2")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "3")
#         set(COMPILER_FLAGS "-O3 -flto -ffast-math")
#     endif()

#     # add debug symbols if CMAKE_BUILD_TYPE is Debug
#     if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#         set(COMPILER_FLAGS "${COMPILER_FLAGS} -g")
#     endif()

#     # add general and architecture-specific flags
#     set(COMPILER_FLAGS "${COMPILER_FLAGS} -Wall -Wextra")
#     if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|i686|amd64|x86_64")
#         set(COMPILER_FLAGS "${COMPILER_FLAGS} -march=native")
#     endif()

# elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
#     set(COMPILER_FLAGS "")
#     if(OPTIMIZATION_LEVEL STREQUAL "0")
#         set(COMPILER_FLAGS "/Od /RTC1")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "1")
#         set(COMPILER_FLAGS "/O1")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "2")
#         set(COMPILER_FLAGS "/O2")
#     elseif(OPTIMIZATION_LEVEL STREQUAL "3")
#         set(COMPILER_FLAGS "/O2 /GL /fp:fast")
#     endif()

#     # add debug symbols if CMAKE_BUILD_TYPE is Debug
#     if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#         set(COMPILER_FLAGS "${COMPILER_FLAGS} /Zi")
#     endif()

#     # add general and architecture-specific flags
#     set(COMPILER_FLAGS "${COMPILER_FLAGS} /W4 /GS-")
#     if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|i686|amd64|x86_64")
#         set(COMPILER_FLAGS "${COMPILER_FLAGS} /arch:AVX2")
#     endif()
# endif()

# shared core library
add_library(Core SHARED ${NxisCoreSource})
#target_compile_options(Core PUBLIC ${COMPILER_FLAGS})
target_include_directories(Core PUBLIC "../inc")
target_link_libraries(Core PUBLIC SDL3::SDL3)

# installation rules
# install(TARGETS CoreShared ARCHIVE DESTINATION lib LIBRARY DESTINATION lib) # add CoreStatic later
# install(DIRECTORY "../inc" DESTINATION include/Nexis/Core)