cmake_minimum_required (VERSION 3.1)
project (kmeans)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_pattern test_pattern.cpp pattern.hpp pattern.cpp)
add_executable(test_kmeans test_kmeans.cpp kmeans.cpp kmeans.hpp pattern.hpp pattern.cpp)
