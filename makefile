OBJS = OBJ/list.o OBJ/graf.o

BIN/graf : main.c graph.h LIB/libiblist.a #Ne recompile la librairie que si elle a été modifiée
	@echo
	@echo "Compiling program ..."
	gcc -o BIN/graf main.c -L LIB/ -liblist

LIB/libiblist.a : liblist/list.c liblist/list.h
	@echo "Compiling liblist ..."
	gcc -o OBJ/list.o -c liblist/list.c -lm -Wall -Wextra
	@ ar rc LIB/libiblist.a OBJ/*.o
	@ cp LIB/libiblist.a ../lib