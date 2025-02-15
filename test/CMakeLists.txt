enable_testing()

# add_executable(
#   test_polynomial
#   test_polynomial.cpp
# )
# target_link_libraries(
#   test_polynomial
#   cshape
#   GTest::gtest_main
# )
add_executable(
  test_parameter
  test_parameter.cpp
)
target_link_libraries(
  test_parameter
  cshape
  GTest::gtest_main
)


include(GoogleTest)
# gtest_discover_tests(test_polynomial)
gtest_discover_tests(test_parameter)

