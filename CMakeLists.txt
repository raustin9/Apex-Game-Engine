include(FetchContent)
cmake_minimum_required(VERSION 3.10)

project(ApexEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(APEX_ENGINE_SUBPROJECT ON)
endif ()

# Engine source
add_subdirectory(apex)

if (NOT APEX_ENGINE_SUBPROJECT)
    add_subdirectory(tests)

    add_subdirectory(apps/window)
endif ()
