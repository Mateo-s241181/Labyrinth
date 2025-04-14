#main executable
add_executable(Maze main.cpp maze.cpp main.cpp)

#test executable
add_executable(maze_tests maze_tests.cpp maze.cpp)
target_link_libraries(maze_tests Catch2::Catch2WithMain)

catch_discover_tests(maze_tests)