#include <stdbool.h>
#include <string.h>
#import "graph.h"

int main() {
	printf("Hello, World!\n");
	menu();
	return 0;
}

void menu() {
	char val[50] = "";
	char val2[50] = "";

	printf("===== Menu =====\n");
	printf("1. CreateGraph \n");
	printf("2. ... \n");

	while (fgets(val, 50, stdin) && atoi(val) != 9) {
		if (atoi(val) == 1) {
			printf("Nb max nodes\n");
			fgets(val, 50, stdin);
			printf("0 No directed, 1 Directed\n");
			fgets(val2, 50, stdin);
			createGraph(atoi(val), atoi(val2) == 0 ? false : true);
			printf("Graph G with %i max nodes, %sdirected created \n", g.nbMaxNodes, g.isDirected ? "" : "no ");
		}
	}
}

void createGraph(int maxNodes, bool directed) {
	g.isDirected = directed;
	g.nbMaxNodes = maxNodes;
}

