#include "graph.h"

int main() {
	printf("Hello, World!\n");
	menu();
	return 0;
}

void menu() {
	char val[50] = "";
	char val2[50] = "";
	displayMenu();
	while (fgets(val, 50, stdin) && atoi(val) != 9) {
		switch (atoi(val)) {
			case 1:
				printf("Nb max nodes\n");
				fgets(val, 50, stdin);
				printf("0 No directed, 1 Directed\n");
				fgets(val2, 50, stdin);
				createGraph(atoi(val), atoi(val2) == 0 ? false : true);
				printf("Graph G with %i max nodes, %sdirected created \n", g.nbMaxNodes, g.isDirected ? "" : "no ");
				break;
			case 2:
				break;
			case 3:
				for (int i = 0; i < g.nbMaxNodes; ++i) {
					printf("numNode\n");
					fgets(val, 50, stdin);
					printf("valNode\n");
					fgets(val2, 50, stdin);
					base_addToStart(g.list, atoi(val), atoi(val2));
				}
				break;

			default:
			case 9 :
				exit(EXIT_SUCCESS);
		}
		displayMenu();
	}
}

void displayMenu() {
	printf("\n===== Menu =====\n\n");
	printf("1. CreateGraph \n");
	printf("2. LoadGraph \n");
	printf("3. AddNodes \n");
	printf("4. AddEdges \n");
}

void createGraph(int maxNodes, bool directed) {
	g.isDirected = directed;
	g.nbMaxNodes = maxNodes;
	g.list = newChainedList();
}

