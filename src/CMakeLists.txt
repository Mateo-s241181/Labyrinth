#main executable
add_executable(Maze main.cpp)

#test executable
add_executable(maze_tests maze_tests.cpp)
target_link_libraries(maze_tests Catch2::Catch2WithMain)

catch_discover_tests(maze_tests)