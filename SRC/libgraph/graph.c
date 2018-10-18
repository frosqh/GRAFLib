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

	return base_addToEnd(g.list[start], end, weight);
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

int deleteGraph(struct Graph *g) {
	if (g == NULL) return -1;
	if (g->list != NULL) {
		for (int node = 0; node < g->nbMaxNodes; ++node)
			if (g->list[node] != NULL) freeList(g->list[node]);
	}
	g->isDirected = NULL;
	g->nbMaxNodes = NULL;
	free(g->list);
	return 0;
}

int freeGraph(struct Graph g){
	printf("Plop ! ");
	int i;
	printf("%d\n",g.nbMaxNodes);
	for(i=0;i<g.nbMaxNodes;i++){
		printf("%d\n",g.list[i]->value);
		int val = freeList(g.list[i]);
		if (val){
			exit(val);
		}
	}
	return 0;
}

struct Graph loadGraphFromString(char* file){
	char buff[1024];
	char buffnd[16];
	char buffrd[16];
	bool sE;
	int c;
	int index = 0;
	int step = 0;
	int node;
	int i,j;
	int maxNode = -1;
	bool directed = false;
	bool oneLast = true;
	struct Graph g;
	FILE *f = fopen(file,"r");
	if (!f) exit(EXIT_FAILURE);
	bool cont = (c=fgetc(f))!=EOF;
	while (cont){
		if (c!='\n' && oneLast){
			buff[index] = c;
			index++;
		} else {
			buff[index] = '\0';
			for (int k = 0;k<10;k++){
				buff[index+k]='\0';
			}
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
						break;
					case 2:
						g = createGraph(maxNode, directed);
						step++;
					case 3:
						i=0;
						while(buff[i]!=':'){
							buffnd[i]=buff[i];
							i++;
						}
						buffnd[i]='\0';
						node = atoi(buffnd);
						addNode(g, node);
						while(buff[i] != 0){
							sE=false;
							i++;
							i++;
							i++;
							j=0;
							while (buff[i]!=')'){
								if (!sE){
									if (buff[i] != '/'){
										buffnd[j] = buff[i];
										j++;
									}
									else{
										buffnd[j] = '\0';
									 	sE = true;
									 	j = 0;
									}
									i++;

								} else {
									buffrd[j]=buff[i];
									i++;
									j++; 
								}
							}
							buffrd[j] = '\0';
							addNode(g, atoi(buffnd));
							addEdge(g, node, atoi(buffnd), atoi(buffrd));
							i++;
						}
						break;
				}
			}
		}
		if (oneLast){
			oneLast = (c=fgetc(f))!=EOF;
		} else {
			cont = false;
		}
	}/*
	buff[index] = '\0';
	for (int k = 0;k<10;k++){
				buff[index+k]='\0';
	}
	i=0;
	while(buff[i]!=':'){
		buffnd[i]=buff[i];
		i++;
	}
	buffnd[i]='\0';
	node = atoi(buffnd);
	addNode(g, node);
	while(buff[i] != 0){
		sE=false;
		i++;
		i++;
		i++;
		j=0;
		printf("%c\n",buff[i]);
		while (buff[i]!=')'){
			if (!sE){
				if (buff[i] != '/'){
					buffnd[j] = buff[i];
					j++;
				}
				else{
					buffnd[j] = '\0';
				 	sE = true;
				 	j = 0;
				}
				i++;

			} else {
				buffrd[j]=buff[i];
				i++;
				j++; 
			}
		}
		buffrd[j] = '\0';
		addNode(g, atoi(buffnd));
		addEdge(g, node, atoi(buffnd), atoi(buffrd));
		i++;
	}*/
	return g;
}


void graphToString(struct Graph g,char* str){
	int currentIndex = 0;
	char buffnb[16];
	sprintf(buffnb, "%d", g.nbMaxNodes);
	int i = 0;
	struct cchainedList **lists = g.list;
	while(buffnb[i] != 0){
		str[currentIndex++] = buffnb[i];
		i++;
	}
	str[currentIndex++]='\n';
	if (g.isDirected)
		str[currentIndex++]='n';
	else
		str[currentIndex++]='y';
	str[currentIndex++]='\n';
	for (i = 0; i<g.nbMaxNodes; i++){
		if (lists[i] != NULL){
			sprintf(buffnb, "%d", i);
			int j = 0;
			while(buffnb[j] != 0){
				str[currentIndex++] = buffnb[j];
				j++;
			}
			str[currentIndex++]=':';
			str[currentIndex++]=' ';
			struct cchainedList* list = goToStart(lists[i]);
			list = goToStart(list);
			list = list->next;
			while (list->value != -1){
				str[currentIndex++]='(';
				sprintf(buffnb, "%d", list->value);
				j=0;
				while(buffnb[j] != 0){
					str[currentIndex++] = buffnb[j];
					j++;
				}
				str[currentIndex++]='/';
				sprintf(buffnb, "%d", list->secondValue);
				j=0;
				while(buffnb[j] != 0){
					str[currentIndex++] = buffnb[j];
					j++;
				}
				str[currentIndex++]=')';
				str[currentIndex++]=',';
				str[currentIndex++]=' ';
				list = list->next;
			}
			currentIndex--;
			currentIndex--;



			str[currentIndex++] = '\n';
		}
	}
}
