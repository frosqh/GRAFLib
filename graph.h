#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

#ifndef TP2GRAPH_GRAPH_H
#define TP2GRAPH_GRAPH_H

struct Graph g;

char val[50] = "";
char val2[50] = "";

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct cchainedList **list;
};

void createGraph(int maxNodes, bool directed);

void addEdge(int start, int end, int weight);

void menu();

void displayMenu();

#endif //TP2GRAPH_GRAPH_H
