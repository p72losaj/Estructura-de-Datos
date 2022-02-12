cmake_minimum_required (VERSION 3.1)
project (packet_processor)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_queue test_queue.cpp queue.hpp)
add_executable(test_packet_processor test_packet_processor.cpp packet_processor.cpp packet_processor.hpp queue.hpp)
