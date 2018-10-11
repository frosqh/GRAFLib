OBJS = OBJ/list.o OBJ/graf.o

BIN/graf : SRC/main.c SRC/graph.h SRC/menu.h LIB/libiblist.a LIB/libibgraph.a#Ne recompile la librairie que si elle a été modifiée
	@echo
	@echo "Compiling program ..."
	gcc -o BIN/graf SRC/main.c -L LIB/ -liblist -libgraph

LIB/libibgraph.a : SRC/libgraph/graph.c SRC/libgraph/graph.h
	@echo "Compiling libgraph ..."
	gcc -o OBJ/graph.o -c SRC/libgraph/graph.c -lm -Wall -Wextra
	@ ar rc 	LIB/libibgraph.a OBJ/graph.o
	@ cp LIB/libibgraph.a ../LIB

LIB/libiblist.a : SRC/liblist/list.c SRC/liblist/list.h
	@echo "Compiling liblist ..."
	gcc -o OBJ/list.o -c SRC/liblist/list.c -lm -Wall -Wextra
	@ ar rc LIB/libiblist.a OBJ/list.o
	@ cp LIB/libiblist.a ../lib