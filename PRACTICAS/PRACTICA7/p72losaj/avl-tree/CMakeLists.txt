cmake_minimum_required (VERSION 3.1)
project (avl_tree)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_bstree test_avltree.cpp avltree.hpp)
target_compile_definitions(test_bstree PRIVATE "-D__FIRST_DELIVERY")

add_executable(test_avltree test_avltree.cpp avltree.hpp)

