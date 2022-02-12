cmake_minimum_required (VERSION 3.1)
project (maze_solver)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_maze_solver test_maze_solver.cpp maze_solver.hpp maze_solver.cpp a_star_algorithm.hpp graph.hpp graph_utils.hpp)
