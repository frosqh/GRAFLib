
#ifndef TP2GRAPH_HEURISTIQUE_H
#define TP2GRAPH_HEURISTIQUE_H

#include "../libgraph/graph.h"

struct NodeGraph {
	struct cchainedList **list;
};

bool firstSearch(struct Graph G, int tab[], int index, int start, int end);

bool randomSearch(struct Graph G, int tab[], int index, int start, int end);

void mixNodeNumber(int *tableau, int taille);

#endif //TP2GRAPH_HEURISTIQUE_H
