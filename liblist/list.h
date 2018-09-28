#include <stdio.h>
#include <stdlib.h>

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

//void addToEnd(struct cchainedList* list, int value);
void var_addToEnd(values in);
void var_addToStart(values in);
//void addToStart(struct cchainedList* list, int value);
void base_addToEnd(struct cchainedList* list, int value, int secondValue);
void base_addToStart(struct cchainedList* list, int value, int secondValue);
struct cchainedList* newChainedList();
struct cchainedList* goToStart(struct cchainedList* list);
char* listToString(struct cchainedList* list);
void removeFromList(struct cchainedList* list);
void removeIndex(struct cchainedList* list, int i);
static struct cchainedList* auxRemove(struct cchainedList* list, int diff);