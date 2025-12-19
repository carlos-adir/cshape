project(CShape)
cmake_minimum_required(VERSION 3.16)

# Collect all .cpp files under src (including subfolders)
file(GLOB_RECURSE SRC_FILES
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Optionally filter out CMakeLists.cpp or unwanted files (not usually needed)
# list(FILTER SRC_FILES EXCLUDE REGEX ".*excluded_file.cpp$")

add_library(cshape SHARED ${SRC_FILES})

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Recommended: set C++ standard
target_compile_features(cshape PUBLIC cxx_std_17)