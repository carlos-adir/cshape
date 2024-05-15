enable_testing()

add_executable(
  test_nurbs
  test_nurbs.cpp
)
target_link_libraries(
  test_nurbs
  cshape
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_nurbs)
