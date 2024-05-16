enable_testing()

add_executable(
  test_nurbs
  test_nurbs.cpp
)
add_executable(
  test_geom
  test_geom.cpp
)
target_link_libraries(
  test_nurbs
  cshape
  GTest::gtest_main
)
target_link_libraries(
  test_geom
  cshape
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(test_nurbs)
gtest_discover_tests(test_geom)
