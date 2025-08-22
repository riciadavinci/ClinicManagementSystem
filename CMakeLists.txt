cmake_minimum_required(VERSION 3.16)

project(GroceryExpenseTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(PROJECT_CORE_PATH "${PROJECT_APP_PATH}/core")
set(PROJECT_WIDGETS_PATH "${PROJECT_APP_PATH}/widgets")
set(PROJECT_DATABASE_PATH "${PROJECT_APP_PATH}/database")

# ----------------------------------------
# Compiler Specific Flags:
# ----------------------------------------
if (MSVC) 
    message(STATUS "Using MSVC Compiler")
    add_compile_definitions(NOMINMAX _CRT_SECURE_NO_WARNINGS)
    # Common MSVC Flags
    add_compile_options(/W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC Compiler")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang Compiler")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# ----------------------------------------
# Build Type Flags:
# ----------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose Debug or Release" FORCE)
endif ()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    if (MSVC)
        # Enable debugging info
        add_compile_options(/Zi)
    else ()
        add_compile_options(-g)
    endif ()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    if (MSVC)
        # Enable debugging info
        add_compile_options(/O2)
    else ()
        add_compile_options(-O3 -march=native)
    endif ()
endif ()

# ----------------------------------------
# FetchContent - Google Test (in Debug only)
# ----------------------------------------
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/app/dependencies")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CTest)
    enable_testing()

    FetchContent_Declare(
        googletest
        URL "https://github.com/google/googletest/archive/refs/heads/main.zip"
    )

    FetchContent_MakeAvailable(googletest)
endif ()

add_subdirectory(app)
