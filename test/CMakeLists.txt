include(CTest)

add_executable(test_logger main.cpp)
target_link_libraries(test_logger Toolbox)

add_test(NAME Runs COMMAND test_logger)

add_test(NAME Version COMMAND test_logger)
set_tests_properties(Version PROPERTIES PASS_REGULAR_EXPRESSION "Toolbox version ${Toolbox_VERSION_MAJOR}.${Toolbox_VERSION_MINOR}")
