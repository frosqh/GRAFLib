#include "graph.h"

void createGraph(int maxNodes, bool directed) {
	g.isDirected = directed;
	g.nbMaxNodes = maxNodes;
	g.list = malloc(maxNodes * sizeof(struct cchainedList));
	//for (int i = 0; i < maxNodes; ++i) g.list[i] = newChainedList();
}

int addEdge(int start, int end, int weight) {
	if (g.list[start] == NULL || g.list[end] == NULL) {
		printf("Error, node not previously added\n");
		return -1;
	}

	return base_addToStart(g.list[start], end, weight);

}
