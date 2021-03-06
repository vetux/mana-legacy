cmake_minimum_required(VERSION 3.0.0)

project(Mana-Legacy)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE -O3)
endif ()

include(cmake/imgui.cmake)
include(cmake/implot.cmake)
include(cmake/extern.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug Build")
    add_compile_definitions("MANA_DEBUG_BUILD")
else ()
    message("Release Build")
endif ()

include(cmake/config.cmake)

if (UNIX)
    add_compile_definitions(MANA_EXPORT=__attribute__\(\(visibility\("default"\)\)\))
elseif (WIN32)
    add_compile_definitions(MANA_EXPORT=__declspec\(dllexport\))
else ()
    add_compile_definitions(MANA_EXPORT=)
endif ()

include(cmake/engine.cmake)
include(cmake/editor.cmake)
include(cmake/sample.cmake)

if(UNIX AND CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(mana-engine PUBLIC -fvisibility=hidden)
endif()