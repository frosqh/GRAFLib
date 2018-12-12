OBJS = OBJ/list.o OBJ/graf.o

BIN/graf : SRC/main.c SRC/menu.h LIB/libiblist.a LIB/libibgraph.a LIB/libibflow.a#Ne recompile la librairie que si elle a été modifiée
	@echo "Compiling program ..."
	gcc -o BIN/graf SRC/main.c -LLIB/ -libgraph -liblist -libflow -ISRC/liblist -ISRC/libgraph -ISRC/libflow

LIB/libibgraph.a : SRC/libgraph/graph.c SRC/libgraph/graph.h
	@echo "Compiling libgraph ..."
	gcc -o OBJ/graph.o -c SRC/libgraph/graph.c -lm -Wall -Wextra -std=c99
	@ ar rc 	LIB/libibgraph.a OBJ/graph.o
	@ cp LIB/libibgraph.a ../LIB

LIB/libiblist.a : SRC/liblist/list.c SRC/liblist/list.h
	@echo "Compiling liblist ..."
	gcc -o OBJ/list.o -c SRC/liblist/list.c -lm -Wall -Wextra
	@ ar rc LIB/libiblist.a OBJ/list.o
	@ cp LIB/libiblist.a ../lib

LIB/libibflow.a : SRC/libflow/max_flow.c SRC/libflow/max_flow.h
	@echo "Compiling libflw ..."
	gcc -o OBJ/flow.o -c SRC/libflow/max_flow.c -lm -Wall -Wextra -std=c99
	@ ar rc 	LIB/libibflow.a OBJ/flow.o
	@ cp LIB/libibflow.a ../LIB

clean : 
	@echo "Deleting .o files ..."
	@rm OBJ/*.o
	@echo "Deleting .a files ..."
	@rm LIB/*.a
	@echo "Deleting bin file ..."
	@rm BIN/graf