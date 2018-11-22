
#include "heuristique.h"
#include "../../../../../../usr/include/string.h"
#include "../../../../../../usr/include/stdlib.h"


void randpath(struct Graph G, int startNode, int endNode) {

}

/**
 * Retourne le premier chemin valide de start à end
 *
 * @param G : Le Graph
 * @param tab : Le tableau contenant le chemin valide
 * @param index : L'index de position dans le tableau de chemin
 * @param start : Valeur du noeud de départ
 * @param end : Valeur du noeud d'arrivé
 */
bool firstSearch(struct Graph G, int tab[], int index, int start, int end) {
	if (start == end) return true;

	struct cchainedList *node = G.list[start];
	int tabTmp[sizeof(tab)];

	while (node->next->value != -1) {
		node = node->next;
		memcpy(tabTmp, tab, sizeof(tab));
		tabTmp[index + 1] = node->value;
		bool pathFound = firstSearch(G, tabTmp, index + 1, node->value, end);
		if (pathFound) {
			tab = tabTmp;
			return true;
		}

	}

	return false;
}

/**
 * Retourne un chemin aléatoire valide de start à end
 *
 * @param G : Le Graph
 * @param tab : Le tableau contenant le chemin valide
 * @param index : L'index de position dans le tableau de chemin
 * @param start : Valeur du noeud de départ
 * @param end : Valeur du noeud d'arrivé
 */
bool randomSearch(struct Graph G, int tab[], int index, int start, int end) {
	if (start == end) return true;

	struct cchainedList *node = G.list[start];
	int tabTmp[sizeof(tab)];
	int nodeTrue[sizeof(tab)];
	int indexNodeTrue = 0;

	int nbNodes = 0;
	while (node->next->value != -1) nbNodes++;

	int indexRand[nbNodes];
	for (int i = 0; i < nbNodes; ++i) {
		node = node->next;
		indexRand[i] = node->value;
	}
	mixNodeNumber(indexRand, nbNodes);

	bool result_ok = false;
	for (int j = 0; j < nbNodes && !result_ok; ++j) {
		while (node->next->value != indexRand[j]) node = node->next;
		memcpy(tabTmp, tab, sizeof(tab));
		tabTmp[index + 1] = node->value;
		bool pathFound = randomSearch(G, tabTmp, index + 1, node->value, end);
		if (pathFound) {
			tab = tabTmp;
			result_ok = true;
		}
	}

	return result_ok;
}

/**
 * Mélange un tableau en intervertissant aléatoirement ses valeurs
 *
 * @param tableau : Le tableau
 * @param taille : la taille du tableau
 */
void mixNodeNumber(int *tableau, int taille) {
	int i = 0;
	int randChange = 0;
	int temp = 0;

	for (i = 0; i < taille; i++) {
		randChange = rand() % taille;
		temp = tableau[i];
		tableau[i] = tableau[randChange];
		tableau[randChange] = temp;
	}
}
