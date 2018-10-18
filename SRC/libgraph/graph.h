#include <stdbool.h>
#ifndef __STDIO_H
	#define __STDIO_H
	#include <stdio.h>
#endif
#ifndef __STDLIB_H
	#define __STDLIB_H
	#include <stdlib.h>
#endif
#ifndef __STRING_H
	#define __STRING_H
	#include <string.h>
#endif
#include "../liblist/list.h"

#ifndef TP2GRAPH_GRAPH_H
#define SIZE 1024
#define TP2GRAPH_GRAPH_H

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct cchainedList **list;
};

struct Graph createGraph(int maxNodes, bool directed);

int addNode(struct Graph g, int numnode);

int addEdge(struct Graph g, int start, int end, int weight);

struct Graph loadGraphFromString(char* file);

int removeNode(struct Graph g, int numnode);

int removeEdge(struct Graph g, int start, int end);

int deleteGraph(struct Graph g);

void graphToString(struct Graph g, char* str);

int freeGraph(struct Graph g);

#endif //TP2GRAPH_GRAPH_H
