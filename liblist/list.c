/*
**********************************************************
*
* Programme : list.c
*
* ecrit par : Gautier Raimondi
*
* resume : Fournit une API d'utilisation de liste doublement
*		   chaînée avec sentinelle possédant deux valeurs.
*
* date : 28/09/2018
*
***********************************************************
*/

#include "list.h"

#define addToEnd(...) var_addToEnd((values){__VA_ARGS__});
#define addToStart(...) var_addToStart((values){__VA_ARGS__});


int main(int argc, char* argv){
	struct cchainedList* list= newChainedList();
	addToStart(list, 5);
	addToStart(list, 6);
	addToEnd(list, 13,9);
	struct cchainedList *secondList = list->next;
	addToStart(secondList, 9);
	removeIndex(list, 2);
	printf("1st : %d\n", list->value);
	printf("2nd : %d\n", secondList->value);
	printf("Last : %d\n", list->prev->value);
	printf("Start : %d\n", goToStart(list)->next->value);
	freeList(list);
}


/*
* Fonction : newChainedList
*
* Parametres :
*
* Retour : struct cchainedList*, pointeur sur une nouvelle liste doublement chaînée.
*
* Description : Crée une nouvelle liste chaînée en mémoire,
*	 			initialisée comme une liste ne contenant qu'une sentinelle.
*
*/
struct cchainedList* newChainedList(){
	struct cchainedList* newList = malloc(sizeof(struct cchainedList));

	newList->value = -1;
	newList->secondValue = -1;
	newList->prev = newList;
	newList->next = newList;
	
	return newList;
}


/*
* Fonction : base_addToEnd
*
* Parametres : struct cchainedList* list, pointeur vers un élément de la liste chaînée (non NULL).
* 			   int value, la valeur de l'élément à ajouter (différent de -1).
			   int secondValue, la seconde valeur de l'élément à ajouter.
*
* Retour : 3 si list est NULL, 4 si value est -1 ou 0 si l'ajout s'est déroulé sans accroc.
*
* Description : Ajoute un élément passé en à la fin de la liste passé en paramètre,
*				i.e avant l'élément pointé par list.
*
*/
int base_addToEnd(struct cchainedList* list, int value, int secondValue){
	if (list == (struct cchainedList*) NULL) {
		return 3;
	}
	if (value == -1) {
		return 4;
	}

	struct cchainedList* newList = malloc(sizeof(struct cchainedList));

	newList->prev = list->prev ; 
	newList->value = value;
	newList->secondValue = secondValue;
	newList->next = list;
	(list->prev)->next = newList;
	list->prev = newList;

	return 0;
}


/*
* Fonction : var_addToEnd
*
* Parametres : values in, 
*
* Retour : rien
*
* Description : cette fonction n’existe pas.
*
*/
int var_addToEnd(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;

	return base_addToEnd(list_out, value_out, secondValue_out);
}


int base_addToStart(struct cchainedList* list, int value, int secondValue){
	if (list==NULL) {
		return 3;
	}
	if (value == -1) {
		return 4;
	}

	struct cchainedList* newList = malloc(sizeof(struct cchainedList));

	newList->value = value;
	newList->secondValue = secondValue;
	newList->prev = list;
	newList->next = list->next;
	list->next->prev = newList;
	list->next = newList;

	return 0;
}


int var_addToStart(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;

	return base_addToStart(list_out, value_out, secondValue_out);
}


struct cchainedList* goToStart(struct cchainedList* list){
	return list->value == -1 ? list : goToStart(list->next);
}


int freeList(struct cchainedList* list){
	list = goToStart(list)->prev;

	while (list->value != -1) {
		struct cchainedList* tmpList = list->prev;
		free(list);
		list = tmpList;
	}

	free(list);

	return 0;
}


int removeFromList(struct cchainedList* list){
	if (list->value == -1) {
		return 2;
	}

	list->prev->next = list->next;
	list->next->prev = list->prev;
	free(list);

	return 0;
}


int removeValue(struct cchainedList* list, int value){
	if (value < 0) {
		return 1;
	}

	struct cchainedList* startList = goToStart(list);

	while (startList->value != value){
		startList = startList->next;
	}

	removeFromList(startList);

	return 0;
}


int removeIndex(struct cchainedList* list, int i){
	if (i < 0) {
		return 1;
	}

	struct cchainedList* startList = goToStart(list);

	while (i > 0) {
		startList = startList->next;
		i--;
	}

	removeFromList(startList);

	return 0;
}
