#include "graph.h"

struct Graph createGraph(int maxNodes, bool directed) {
	struct Graph g;
	g.isDirected = directed;
	g.nbMaxNodes = maxNodes;
	g.list = malloc(maxNodes * sizeof(struct cchainedList));
	return g;
}

int addNode(struct Graph g, int numnode) {
	if (g.list[numnode] != NULL) return -1;
	if (numnode > g.nbMaxNodes) return -2;

	g.list[numnode] = newChainedList();
	return 0;
}

int addEdge(struct Graph g, int start, int end, int weight) {
	if (g.list[start] == NULL || g.list[end] == NULL) {
		printf("Error, node not previously added\n");
		return -1;
	}

	return base_addToStart(g.list[start], end, weight);
}

int removeEdge(struct Graph g, int start, int end) {
	if (g.list[start] == NULL) {
		printf("Error, node (and edge) not exist\n");
		return -1;
	}

	return removeValue(g.list[start], end);
}

int deleteGraph() {

}
