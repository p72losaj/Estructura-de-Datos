cmake_minimum_required (VERSION 3.1)
project (graph_traversal)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_create_graph test_create_graph.cpp graph.hpp graph_utils.hpp city.hpp city.cpp)
add_executable(test_traversals test_traversals.cpp graph_traversals.hpp graph.hpp graph_utils.hpp)

