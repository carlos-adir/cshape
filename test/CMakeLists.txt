enable_testing()

add_executable(
  test_linear_analytic
  test_linear_analytic.cpp
)
add_executable(
  test_polynomial
  test_polynomial.cpp
)
target_link_libraries(
  test_linear_analytic
  cshape
  GTest::gtest_main
)
target_link_libraries(
  test_polynomial
  cshape
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(test_linear_analytic)
gtest_discover_tests(test_polynomial)

