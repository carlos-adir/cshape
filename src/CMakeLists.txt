project(CShape)
cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SRC_FILES
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(cshape SHARED ${SRC_FILES})

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/cshape
)

# Recommended: set C++ standard
target_compile_features(cshape PUBLIC cxx_std_17)
