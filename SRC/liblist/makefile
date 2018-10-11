.PHONY : clean

List: list.c list.h
	gcc -c list.c -lm -Wall -Wextra
	ar rv libiblist.a list.o

clean:
	rm *.o

bigclean:clean
	rm *.a