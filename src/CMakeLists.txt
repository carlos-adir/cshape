project(CShape)

# add_library(cshape SHARED analytic.cpp polynomial.cpp)
# add_library(cshape SHARED parameter.cpp)
add_library(cshape SHARED bool2d.cpp)

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
