enable_testing()

add_executable(
  test_linear_analytic
  test_linear_analytic.cpp
)
target_link_libraries(
  test_linear_analytic
  cshape
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(test_linear_analytic)

