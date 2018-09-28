#include "list.h"
#define addToEnd(...) var_addToEnd((values){__VA_ARGS__});
#define addToStart(...) var_addToStart((values){__VA_ARGS__});

int main(int argc, char* argv){
	struct cchainedList* list= newChainedList(); //-1;6;9;5;13
	addToStart(list, 5);
	addToStart(list, 6);
	addToEnd(list, 13,9);
	struct cchainedList *secondList = list->next;
	addToStart(secondList,9);
	removeIndex(list,2);
	printf("1st : %d\n",list->value);
	printf("2nd : %d\n",secondList->value);
	printf("Last : %d\n",list->prev->value);
	printf("Start : %d\n",goToStart(list)->next->value);
	freeList(list);
}

void base_addToEnd(struct cchainedList* list, int value, int secondValue){
	if (list==NULL){
		printf("Erf ! \n");
		exit(3);
	}
	if (value == -1){
		printf("Ack ! \n");
		exit(4);
	}
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));
	newList->prev = list->prev ; 
	newList->value = value;
	newList->secondValue = secondValue;
	newList->next = list;
	(list->prev)->next = newList;
	list->prev = newList;
}

void freeList(struct cchainedList* list){
	list = goToStart(list)->prev;
	while (list->value != -1){
		printf("%d\n",list->value);
		struct cchainedList* tmpList = list->prev;
		free(list);
		printf("Done");
		list = tmpList;
	}
	printf("%d\n",list->value);
	free(list);
}


void var_addToEnd(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;
	base_addToEnd(list_out, value_out, secondValue_out);
}

void base_addToStart(struct cchainedList* list, int value, int secondValue){
	if (list==NULL){
		printf("Erf ! \n");
		exit(3);
	}
	if (value == -1){
		printf("Ack ! \n");
		exit(4);
	}

	struct cchainedList* newList = malloc(sizeof(struct cchainedList));

	newList->value = value;
	newList->secondValue = secondValue;
	newList->prev = list;
	newList->next = list->next;

	list->next->prev = newList;
	list->next = newList;
}

void var_addToStart(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;
	base_addToStart(list_out, value_out, secondValue_out);
}

struct cchainedList* newChainedList(){
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));
	newList->value = -1;
	newList->secondValue = -1;
	newList->prev = newList;
	newList->next = newList;
	return newList;
}

struct cchainedList* goToStart(struct cchainedList* list){
	if (list->value != -1){
		return goToStart(list->next);
	} else {
		return list;
	}
}

void removeFromList(struct cchainedList* list){
	if (list->value == -1){
		printf("Whoops\n");
		exit(2);
	}

	list->prev->next = list->next;
	list->next->prev = list->prev;
	free(list);
}

void removeIndex(struct cchainedList* list, int i){
	if (i<0){
		printf("Arf\n");
		exit(1);
	}
	struct cchainedList* startList = goToStart(list);
	while (i>0){
		startList = startList->next;
		i--;
	}
	removeFromList(startList);
}

static struct cchainedList* auxRemove(struct cchainedList*list , int diff){
	printf("Valeur : %d; Diff : %d;%d;%d\n",list->value, diff,list->next->value,list->prev->value);
	if (diff==0){
		return list;
	} else {
		return auxRemove(list->next, diff-1);
	}
}

void removeValue(struct cchainedList* list, int value){
	if (value<0){
		printf("Arf ! \n");
		exit(1);
	}
	struct cchainedList* startList = goToStart(list);
	while (startList->value != value){
		startList = startList->next;
	}
	removeFromList(startList);
}