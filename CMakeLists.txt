cmake_minimum_required(VERSION 3.26)
project(custom_memory_allocator_c)

include_directories(includes)

add_executable(custom_memory_allocator_c src/main.c src/fed_allocator.c src/buddy_allocator.c)