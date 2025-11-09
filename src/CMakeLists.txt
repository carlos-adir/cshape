project(CShape)

# add_library(cshape SHARED analytic.cpp polynomial.cpp)
# add_library(cshape SHARED scalar.cpp bool1d.cpp bool2d.cpp)
add_library(cshape SHARED scalar.cpp loggers.cpp rbool.cpp)

target_include_directories(cshape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
