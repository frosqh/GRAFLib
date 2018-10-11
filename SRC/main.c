#include "menu.h"
/*resolved*/
int main() {
	printf("Hello, World!\n");
	menu();
	return 0;
}

void menu() {

	displayMenu();
	while (fgets(val, 50, stdin) && atoi(val) != 9) {
		switch (atoi(val)) {
			case 1:
				printf("Nb max nodes\n");
				fgets(val, 50, stdin);
				printf("0 No directed, 1 Directed\n");
				fgets(val2, 50, stdin);
				createGraph(atoi(val), atoi(val2) != 0);
				printf("Graph G with %i max nodes, %sdirected created \n", g.nbMaxNodes, g.isDirected ? "" : "no ");
				break;
			case 2:
				break;
			case 3:		// Add Nodes
				printf("numNode\n");
				fgets(val, 50, stdin);
				while (atoi(val) != -1) {
					if (atoi(val) < g.nbMaxNodes) {
						g.list[atoi(val)] = newChainedList();
						printf("Node %i added\n", atoi(val));
					} else {
						printf("Error to added node n°%i, Graph G as %i max nodes\n", atoi(val), g.nbMaxNodes);
					}
					printf("numNode (-1 to menu)\n");
					fgets(val, 50, stdin);
				}
				break;
			case 4:		// Add Edges
				printf("Start numNode\n");
				fgets(val, 50, stdin);

				while (atoi(val) != -1) {
					int start = atoi(val);

					printf("End numNode\n");
					fgets(val, 50, stdin);
					int end = atoi(val);

					printf("Weight\n");
					fgets(val2, 50, stdin);

					if (addEdge(start, end, atoi(val2)) == 0) {
						if (!g.isDirected) {
							printf("Symmetric ? y or n\n");
							fgets(val, 50, stdin);
							if (strcmp(val, "y") == 0) {
								printf("ok\n");
								printf("Weight for %i to %i\n", end, start);
								fgets(val2, 50, stdin);
								addEdge(end, start, atoi(val2));
							}
						} else {
							printf("Weight for %i to %i\n", end, start);
							fgets(val2, 50, stdin);
							addEdge(end, start, atoi(val2));
						}
					}


					printf("Start numNode (-1 to menu)\n");
					fgets(val, 50, stdin);
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
	if (g.nbMaxNodes == NULL) {
		printf("1. CreateGraph \n");
		printf("2. LoadGraph \n");
	} else {
		printf("3. AddNodes \n");
		printf("4. AddEdges \n");
		printf("8. DestroyGraph \n");
	}
	printf("9. Exit \n");

}

