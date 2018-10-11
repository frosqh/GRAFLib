cmake_minimum_required(VERSION 3.6)
project(TP2Graph C)

set(CMAKE_C_STANDARD 99)

add_executable(list SRC/liblist/list.c SRC/liblist/list.h)

add_executable(TP2Graph SRC/main.c SRC/liblist/list.c SRC/libgraph/graph.c SRC/menu.h SRC/libgraph/graph.h SRC/liblist/list.h)