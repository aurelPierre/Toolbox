include(CTest)

add_executable(test_logger test_logger.cpp)
target_link_libraries(test_logger Toolbox)

add_executable(test_timer test_timer.cpp)
target_link_libraries(test_timer Toolbox)

add_executable(test_profiler test_profiler.cpp)
target_link_libraries(test_profiler Toolbox)

# Make sure the exec runs without any issue first
add_test(NAME Runs_logger COMMAND test_logger)

add_test(NAME Version COMMAND test_logger)
set_tests_properties(Version PROPERTIES PASS_REGULAR_EXPRESSION "Toolbox version ${Toolbox_VERSION_MAJOR}.${Toolbox_VERSION_MINOR}")

add_test(NAME Runs_timer COMMAND test_timer)

add_test(NAME Runs_profiler COMMAND test_profiler)

