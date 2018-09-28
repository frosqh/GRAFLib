#ifndef __LIST_H
	#define __LIST_H
	#ifndef __STDIO_H
		#define __STDIO_H
		#include <stdio.h>
	#endif
	#ifndef __STDLIB_H
		#define __STDLIB_H
		#include <stdlib.h>
	#endif

	struct cchainedList{
		struct cchainedList* prev;
		int value;
		int secondValue;
		struct cchainedList* next;
	};

	typedef struct {
		struct cchainedList* list;
		int value;
		int secondValue;
	} values;

	
	int var_addToEnd(values in);
	int var_addToStart(values in);
	int freeList(struct cchainedList* list);
	int base_addToEnd(struct cchainedList* list, int value, int secondValue);
	int base_addToStart(struct cchainedList* list, int value, int secondValue);
	struct cchainedList* newChainedList();
	struct cchainedList* goToStart(struct cchainedList* list);
	int removeFromList(struct cchainedList* list);
	int removeIndex(struct cchainedList* list, int i);
	int removeValue(struct cchainedList* list, int value);
#endif