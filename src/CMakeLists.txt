project(CShape)

add_library(cshape SHARED parameter.cpp coordinate.cpp analytic.cpp polynomial.cpp)

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
