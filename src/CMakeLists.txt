add_executable(HelloWorld greet.cpp function.cpp)

add_executable(greet_tests greet_tests.cpp function.cpp)
target_link_libraries(greet_tests Catch2::Catch2WithMain)

catch_discover_tests(greet_tests)