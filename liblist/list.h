#include <stdio.h>
#include <stdlib.h>

struct cchainedList{
	struct cchainedList* prev;
	int value;
	struct cchainedList* next;
};

void addToEnd(struct cchainedList* list, int value);
void addToStart(struct cchainedList* list, int value);
struct cchainedList* newChainedList();
struct cchainedList* goToStart(struct cchainedList* list);
char* listToString(struct cchainedList* list);
void removeFromList(struct cchainedList* list);
void removeIndex(struct cchainedList* list, int i);
static struct cchainedList* auxRemove(struct cchainedList* list, int diff);