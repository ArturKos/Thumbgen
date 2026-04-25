cmake_minimum_required(VERSION 3.14)
project(thumbgen CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ----------------------------------------------------------------------------
# Portable core: pure C++ logic that has no platform dependencies.
# Built and unit-tested on every platform.
# ----------------------------------------------------------------------------
add_library(thumbgen_core STATIC
    src/image_filter.cpp
    src/thumbnail_path.cpp
)
target_include_directories(thumbgen_core PUBLIC include)

# ----------------------------------------------------------------------------
# Windows-only UI executable. Skipped on non-Windows platforms; the BCB6
# project file (Thumbgen.bpr) remains the canonical build for the .exe.
# ----------------------------------------------------------------------------
if(WIN32)
    add_library(thumbgen_engine STATIC src/thumbnail_engine.cpp)
    target_include_directories(thumbgen_engine PUBLIC include)
    target_link_libraries(thumbgen_engine PUBLIC gdiplus)
endif()

# ----------------------------------------------------------------------------
# Tests
# ----------------------------------------------------------------------------
option(THUMBGEN_BUILD_TESTS "Build unit tests" ON)
if(THUMBGEN_BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(thumbgen_tests
        tests/test_image_filter.cpp
        tests/test_thumbnail_path.cpp
    )
    target_link_libraries(thumbgen_tests
        PRIVATE thumbgen_core GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(thumbgen_tests)
endif()
