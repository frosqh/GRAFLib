#include <stdio.h>
#include <stdlib.h>
#import "liblist/list.h"

#ifndef TP2GRAPH_GRAPH_H
#define TP2GRAPH_GRAPH_H

struct Graph g;

struct Graph{
	bool isDirected;
	int nbMaxNodes;
};


void createGraph(int maxNodes, bool directed);

void menu();

#endif //TP2GRAPH_GRAPH_H
