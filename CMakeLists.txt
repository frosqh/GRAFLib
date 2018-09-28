cmake_minimum_required(VERSION 3.6)
project(TP2Graph C)

set(CMAKE_C_STANDARD 99)

add_executable(list liblist/list.c liblist/list.h)

add_executable(TP2Graph main.c liblist/list.c graph.h liblist/list.h)