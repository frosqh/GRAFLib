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
	if (g.list[start] == NULL || g.list[end] == NULL)
		return -1;

	return base_addToStart(g.list[start], end, weight);
}

int removeNode(struct Graph g, int numnode) {
	if (g.list[numnode] == NULL) return -1;

	for (int node = 0; node < g.nbMaxNodes; ++node)
		if (node != NULL && node != numnode)
			removeEdge(g, node, numnode);

	return freeList(g.list[numnode]);
}

int removeEdge(struct Graph g, int start, int end) {
	if (g.list[start] == NULL) return -1;

	return removeValue(g.list[start], end);
}

int deleteGraph(struct Graph g) {

}

struct Graph loadGraphFromString(char* file){
	char buff[1024];
	int c;
	int index = 0;
	int step = 0;
	int maxNode = -1;
	bool directed = false;
	struct cchainedList **lists;
	FILE *f = fopen(file,"r");
	if (!f) exit(EXIT_FAILURE);
	while ((c = fgetc(f)) != EOF){
		if (c!='\n'){
			buff[index] = c;
			index++;
		} else {
			buff[index] = '\0';
			index =0;
			if (buff[0] != '#'){
				switch (step){
					case 0:
						maxNode = atoi(buff);
						step++;
						break;
					case 1:
						if (!strcmp("n",buff)) directed = false;
						else if (!strcmp("y",buff)) directed = true;
						else exit(EXIT_FAILURE);
						step++;
				}
			}
		}
	}
	printf("%d\n",maxNode);
	printf("%d\n",directed);	
}
