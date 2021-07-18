add_executable(basic_test basic_test.cc)
target_link_libraries(basic_test gtest_main gtest)

add_test(NAME basic_test COMMAND basic_test)
