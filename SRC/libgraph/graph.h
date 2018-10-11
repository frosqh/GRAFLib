#include <stdbool.h>
#include "../liblist/list.h"

#ifndef TP2GRAPH_GRAPH_H
#define TP2GRAPH_GRAPH_H

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct cchainedList **list;
};

struct Graph createGraph(int maxNodes, bool directed);

int addEdge(struct Graph g, int start, int end, int weight);

#endif //TP2GRAPH_GRAPH_H
