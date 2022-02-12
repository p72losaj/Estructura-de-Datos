cmake_minimum_required (VERSION 3.1)
project (graphs)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_prim test_prim.cpp prim_algorithm.hpp graph.hpp graph_utils.hpp city.hpp city.cpp)
add_executable(test_kruskal test_kruskal.cpp kruskal_algorithm.hpp disjointsets.hpp graph.hpp graph_utils.hpp city.hpp city.cpp)
