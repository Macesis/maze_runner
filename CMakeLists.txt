cmake_minimum_required(VERSION 3.8)
project(maze_runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

option(DISABLE_ASAN "Do not use Address sanitizer" OFF)

if(NOT DISABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

add_compile_options(-Wall -Wextra -pedantic)

# Use main.cpp to call and debug your functions
add_executable(maze_run maze_runner.cpp maze.cpp empty_path_maze.cpp breadth_first_maze.cpp)

