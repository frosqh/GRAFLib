#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "liblist/list.h"

#ifndef TP2GRAPH_GRAPH_H
#define TP2GRAPH_GRAPH_H

struct Graph g;

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct cchainedList **list;
};

void createGraph(int maxNodes, bool directed);

void menu();

void displayMenu();

#endif //TP2GRAPH_GRAPH_H
