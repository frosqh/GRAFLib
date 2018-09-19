#include "list.h"

int main(int argc, char* argv){
	struct cchainedList list;
	list.value=-1;
	list.prev = &list;
	list.value = -1;
	list.next = &list;
	addToEnd(&list, 5);
	printf("%d\n",list.prev->value);
	printf("%d\n",list.value);
	printf("%d\n",list.next->value);
	/*addToStart(&list, 9);
	printf("%d\n",list.value);
	printf("%d\n",(list.next)->value);
	printf("%d\n",((list.next)->next)->value);
	printf("%d\n",((list.next)->next));*/
}

void addToEnd(struct cchainedList* list, int value){
	struct cchainedList newList;
	newList.prev=list->prev;
	newList.value=value;
	newList.next=list;
	(list->prev)->next = &newList;

	list->prev = &newList;
}

void addToStart(struct cchainedList* list, int value){
	struct cchainedList newList;
	newList.value = value;
	newList.prev = list;
	newList.next = (*list).next;
	(list->next)->prev = &newList;
}