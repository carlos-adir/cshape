enable_testing()
include(GoogleTest)

# search recursively for test_*.cpp (top-level and nested subfolders)
file(GLOB_RECURSE TEST_SOURCES
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/*/test_*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/*/*/test_*.cpp"
)


set(TEST_TARGETS)

foreach(src ${TEST_SOURCES})
  get_filename_component(test_name ${src} NAME_WE)        # file name without extension, e.g. test_binary
  add_executable(${test_name} ${src})
  target_link_libraries(${test_name} PRIVATE cshape GTest::gtest_main)

  # discover tests inside the executable and save the discovered list to a CMake variable
  # gtest_discover_tests will register each TEST as a CTest test
  gtest_discover_tests(${test_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    TEST_LIST_VARIABLE ${test_name}_TESTS
  )

  # enforce dependency chain inside this executable:
  # make test_i+1 depend on test_i so it will run only if the previous passed
  set(_prev "")
  foreach(_t IN LISTS ${test_name}_TESTS)
    if(NOT _prev STREQUAL "")
      set_tests_properties(${_t} PROPERTIES DEPENDS ${_prev})
    endif()
    set(_prev ${_t})
  endforeach()

  list(APPEND TEST_TARGETS ${test_name})
endforeach()

# convenience target: run all tests sequentially and stop on first failure
add_custom_target(run_tests_sequential
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --stop-on-failure -j1
  DEPENDS ${TEST_TARGETS}
  COMMENT "Run all tests sequentially and stop on first failure"
)

# optional: run a single test AFTER the sequential run completes successfully
# configure with -DTEST_TO_RUN=<full_test_name> (example: test_binary.Constructor)
if(DEFINED TEST_TO_RUN)
  add_custom_target(run_one_after_success
    COMMAND ${CMAKE_CTEST_COMMAND} -R ${TEST_TO_RUN} --output-on-failure
    DEPENDS run_tests_sequential
    COMMENT "Run single test ${TEST_TO_RUN} after successful sequential run"
  )
endif()