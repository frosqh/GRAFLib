#include "list.h"
#define BUFFER 128

int main(int argc, char* argv){
	struct cchainedList* list= newChainedList(); //-1;6;9;5;13
	addToStart(list, 5);
	addToStart(list, 6);
	addToEnd(list, 13);
	struct cchainedList secondList;
	secondList = *(list->next);
	addToStart(&secondList,9);
	//removeIndex(secondList.next,2);
	printf("1st : %d\n",list->value);
	printf("2nd : %d\n",secondList.value);
	printf("3rd : %d\n",secondList.next->value);
	printf("4th : %d\n",secondList.next->next->value);
	printf("5th : %d\n",secondList.next->next->next->value);
	printf("6th : %d\n",secondList.next->next->next->next->value);
	printf("7th : %d\n",secondList.next->next->next->next->next->value);
	printf("Last : %d\n",list->prev->value);

	printf("Start : %d\n",goToStart(&secondList)->next->value);


}

void addToEnd(struct cchainedList* list, int value){
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));
	
	newList->prev = list->prev;
	newList->value=value;
	newList->next=list;
	(list->prev)->next = newList;
	list->prev = newList;
}

void addToStart(struct cchainedList* list, int value){
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));

	newList->value = value;
	newList->prev = list;
	newList->next = list->next;

	list->next->prev = newList;
	list->next = newList;
}

struct cchainedList* newChainedList(){
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));
	newList->value = -1;
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
	printf("Suppression de la valeur %d\n",list->value);
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
	printf("%d\n",startList->value);
	removeFromList(auxRemove(startList, i));
}

static struct cchainedList* auxRemove(struct cchainedList*list , int diff){
	printf("Valeur : %d; Diff : %d;%d;%d\n",list->value, diff,list->next->value,list->prev->value);
	if (diff==0){
		return list;
	} else {
		return auxRemove(list->next, diff-1);
	}
}

static void printFirsts(struct cchainedList* list, int n){
	struct cchainedList* newList = goToStart(list);
	for (int i=0;i<n;i++){
		newList = newList->next;
	}
}