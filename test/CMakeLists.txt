enable_testing()

add_executable(
  test_parameter
  test_parameter.cpp
)
add_executable(
  test_coordinate
  test_coordinate.cpp
)
add_executable(
  test_polynomial
  test_polynomial.cpp
)
target_link_libraries(
  test_parameter
  cshape
  GTest::gtest_main
)
target_link_libraries(
  test_coordinate
  cshape
  GTest::gtest_main
)
target_link_libraries(
  test_polynomial
  cshape
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(test_parameter)
gtest_discover_tests(test_coordinate)
gtest_discover_tests(test_polynomial)

