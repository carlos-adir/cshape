cmake_minimum_required(VERSION 3.15)
project(CShape)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)
add_subdirectory(test)
add_subdirectory(src)

option(BUILD_EXAMPLES "Wheter or not to build examples" ON)

if (BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(example)
endif()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

