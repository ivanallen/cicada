add_executable(basic_test basic_test.cc)
add_executable(timer_fd_test timer_fd_test.cc)
add_dependencies(basic_test thirdparty)
add_dependencies(timer_fd_test thirdparty)

target_link_libraries(basic_test gtest_main gtest)
target_link_libraries(timer_fd_test gtest_main gtest cicada_core)

add_test(NAME basic_test COMMAND basic_test)
add_test(NAME timer_fd_test COMMAND timer_fd_test)
