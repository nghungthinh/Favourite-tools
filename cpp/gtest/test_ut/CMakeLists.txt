cmake_minimum_required(VERSION 3.15)
project(test_ut)

# ====== 1. SETUP VARIABLE SECTION ======
# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ====== 2. FIND PACKAGE SECTION ======

# Add GoogleTest (gtest) as a subdirectory (or download it if not present)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.1
)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/../src/prj1
    ${CMAKE_SOURCE_DIR}/../src/prj2
)

# Set source files variable for sub-directories
set(SRC_ROOT_DIR ${CMAKE_SOURCE_DIR}/../src)

set(TEST_PRJ1
    ${SRC_ROOT_DIR}/prj1/status.cpp
)


# Set ENVIRONMENT variable
set(GTEST_LIBRARIES gtest)

# Add subdirectories for tests
add_subdirectory(test_prj1)
add_subdirectory(test_prj2)

# Enable testing
enable_testing()