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

/*int main(){
	struct cchainedList* list = newChainedList();
	freeList(list);
}*/


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
* Description : Ajoute un élément passé en paramètre à la fin de la liste passé en paramètre,
*				i.e avant l'élément pointé par list.prev.
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
* Parametres : values in, une structure composée des attributs struct cchainedList* list, int value et int secondValue
*			   afin de gérer des paramètres par défaut
*
* Retour : 3 si list est NULL, 4 si value est -1 ou 0 si l'ajout s'est déroulé sans accroc.
*
* Description : Ajoute un élément passé en paramètre à la fin de la liste passé en paramètre,
*				i.e avant l'élément pointé par list.prev.
*
*/
int var_addToEnd(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;

	return base_addToEnd(list_out, value_out, secondValue_out);
}


/*
* Fonction : base_addToStart
*
* Parametres : struct cchainedList* list, pointeur vers un élément de la liste chaînée (non NULL).
* 			   int value, la valeur de l'élément à ajouter (différent de -1).
*			   int secondValue, la seconde valeur de l'élément à ajouter.
*
* Retour : 3 si list est NULL, 4 si value est -1 ou 0 si l'ajout s'est déroulé sans accroc.
*
* Description : Ajoute un élément passé en paramètre au début de la liste passé en paramètre,
*				i.e avant l'élément pointé par list.next
*
*/
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


/*
* Fonction : var_addToStart
*
* Parametres : values in, une structure composée des attributs struct cchainedList* list, int value et int secondValue
*			   afin de gérer des paramètres par défaut
*
* Retour : 3 si list est NULL, 4 si value est -1 ou 0 si l'ajout s'est déroulé sans accroc.
*
* Description : Ajoute un élément passé en paramètre à la fin de la liste passé en paramètre,
*				i.e avant l'élément pointé par list.next.
*
*/
int var_addToStart(values in){
	int value_out = in.value ? in.value : -1;
	int secondValue_out = in.secondValue ? in.secondValue : -1;
	struct cchainedList* list_out = in.list ? in.list : NULL;

	return base_addToStart(list_out, value_out, secondValue_out);
}


/*
* Fonction : goToStart
*
* Parametres : struct cchainedList* list, pointeur vers la liste à "rembobiner"
*
* Retour : struct cchainedList*, pointeur sur la sentinelle de la liste passée en paramètre.
*
* Description : Permet de retrouver la sentinelle d'une liste.
*
*/
struct cchainedList* goToStart(struct cchainedList* list){
	return list->value == -1 ? list : goToStart(list->next);
}


/*
* Fonction : freeList
*
* Parametres : struct cchainedList* list, pointeur vers la liste à libérer
*
* Retour : 0 si le free s'est déroulé correctement
*
* Description : Libère la liste spécifiée en mémoire, en libérant chacun de ses éléménts.
*
*/
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


/*
* Fonction : removeFromList
*
* Parametres : struct cchainedList* list, pointeur vers l'élement de la liste à supprimer
*
* Retour : 0 si la suppression s'est bien déroulée
*
* Description : Supprime un élément de la list, en liant les element.next.prev et element.prev.next,
*				et en libérant de la mémoire l'élément.
*
*/
int removeFromList(struct cchainedList* list){
	if (list->value == -1) {
		return 2;
	}

	list->prev->next = list->next;
	list->next->prev = list->prev;
	free(list);

	return 0;
}


/*
* Fonction : removeValue
*
* Parametres : struct cchainedList* list, pointeur vers la liste dont un élément est à supprimer
*			   int value, la valeur de l'élément à supprimer
*
* Retour : 2 si la valeur spécifiée n'est pas dans a liste,  1 si la valeur spécifiée est négative, 0 si la suppression se déroule sans incidents.
*
* Description : Supprime l'élément de valeur donnée de la liste.
*
*/
int removeValue(struct cchainedList* list, int value){
	if (value < 0) {
		return 1;
	}

	struct cchainedList* startList = goToStart(list);

	while (startList->value != value && startList->next->value != -1){
		startList = startList->next;
	}

	if (startList->value == value){
		removeFromList(startList);
		return 0;
	}

	return 2;
}


/*
* Fonction : removeIndex
*
* Parametres : struct cchainedList* list, pointeur vers la liste dont un élément est à supprimer
*			   int i, l'index de l'élément à supprimer.
*
* Retour : 1 si l'index spécifié est négatif, 0 si la suppression se déroule sans incidents.
*
* Description : Supprime l'élément d'index donné de la liste.
*
*/
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
