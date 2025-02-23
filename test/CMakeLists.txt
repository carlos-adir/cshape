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
  test_scalar
  test_scalar.cpp
)
target_link_libraries(
  test_scalar
  cshape
  GTest::gtest_main
)
add_executable(
  test_bool1d
  test_bool1d.cpp
)
target_link_libraries(
  test_bool1d
  cshape
  GTest::gtest_main
)
# add_executable(
#   test_bool2d
#   test_bool2d.cpp
# )
# target_link_libraries(
#   test_bool2d
#   cshape
#   GTest::gtest_main
# )


include(GoogleTest)
# gtest_discover_tests(test_polynomial)
gtest_discover_tests(test_scalar)
gtest_discover_tests(test_bool1d)
# gtest_discover_tests(test_bool2d)

