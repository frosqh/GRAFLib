#include <stdio.h>

#import "graph.h"


int main() {

	Graph g;
	g.isDirected = false;
	g.nbMaxNodes = 4;
	g.adjList = malloc(g.nbMaxNodes*sizeof(Neighbour));

	printf("Hello, World!\n");
	return 0;
}