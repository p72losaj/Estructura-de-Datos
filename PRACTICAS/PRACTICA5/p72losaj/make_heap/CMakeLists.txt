cmake_minimum_required (VERSION 3.1)
project (make_heap)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_heapmin test_heapmin.cpp heap.hpp)
add_executable(test_heapmax test_heapmax.cpp heap.hpp)
add_executable(test_heapsort test_heapsort.cpp heap.hpp heapsort.hpp)
