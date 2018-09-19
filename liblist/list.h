#include <stdio.h>
#include <stdlib.h>

struct cchainedList{
	struct cchainedList* prev;
	int value;
	struct cchainedList* next;
};

void addToEnd(struct cchainedList* list, int value);
void addToStart(struct cchainedList* list, int value);