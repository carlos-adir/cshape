project(CShape)

add_library(cshape SHARED nurbs.cpp)

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
