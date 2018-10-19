/*
**********************************************************
*
* Programme : graph.c
*
* ecrit par : Valentin Bonnal & Gautier Raimondi
*
* resume : Fournit une API d'utilisation de graph
*
* date : 19/10/2018
*
***********************************************************
*/

#include "graph.h"

/**
* Crée un graph et le retourne
 *
 * @param maxNodes : noeuds max
 * @param directed : si le graph est orienté
 * @return : Le graph créé
 */
struct Graph createGraph(int maxNodes, bool directed) {
	struct Graph g;
	g.isDirected = directed;
	g.nbMaxNodes = maxNodes;
	g.list = malloc(maxNodes * sizeof(struct cchainedList));
	return g;
}

/**
* Ajout un noeud à un graph
 *
 * @param g : Le graph
 * @param numnode : le noeud à ajouter
 * @return : 0 si le noeud à bien été ajouté
 * @return : -1 si le noeud est déjà ajouté
 * @return : -2 si le numéro du noeud à ajouter
 * 			 est supérieur au nombre max de noeud du graph
 */
int addNode(struct Graph g, int numnode) {
	if (g.list[numnode] != NULL) return -1;
	if (numnode > g.nbMaxNodes) return -2;

	g.list[numnode] = newChainedList();
	return 0;
}

/**
* Ajout une arête à un graph
 *
 * @param g : Le graph
 * @param start : le noeud de départ
 * @param end : le noeud d'arrivé
 * @param weight : le poids de l'arête
 * @return : 0 si l'arête à bien été ajoutée
 * @return : -1 si le noeud de départ ou d'arrivé n'a pas été ajouté au graph
 * @return : autre, consulter les retours de la fonction "base_addToEnd"
 */
int addEdge(struct Graph g, int start, int end, int weight) {
	if (g.list[start] == NULL || g.list[end] == NULL)
		return -1;

	return base_addToEnd(g.list[start], end, weight);
}

/**
* Supprime le noeud d'un graph et ses arêtes
 *
 * @param g : Le graph
 * @param numnode : le noeud à supprimer
 * @return : 0 si le noeud à bien été supprimé
 * @return : -1 si le noeud n'existe pas
 * @return : autre, consulter les retours de la fonction "freeList"
 */
int removeNode(struct Graph g, int numnode) {
	if (g.list[numnode] == NULL) return -1;

	for (int node = 0; node < g.nbMaxNodes; ++node)
		if (node != NULL && node != numnode)
			removeEdge(g, node, numnode);

	return freeList(g.list[numnode]);
}

/**
* Supprime l'arête d'un graph
 *
 * @param g : Le graph
 * @param start : le noeud de départ
 * @param end : le noeud d'arrivé
 * @return : 0 si l'arête à bien été supprimée
 * @return : -1 si l'arête n'existe pas
 * @return : autre, consulter les retours de la fonction "removeValue"
 */
int removeEdge(struct Graph g, int start, int end) {
	if (g.list[start] == NULL) return -1;

	return removeValue(g.list[start], end);
}

/**
* Supprime un graph, ses arêtes, ses noeuds
 *
 * @param g : Le graph
 * @return : 0 si le graph à bien été supprimé
 * @return : -1 si le graph n'existe pas
 */
int deleteGraph(struct Graph *g) {
	if (g == NULL) return -1;
	if (g->list != NULL) {
		for (int node = 0; node < g->nbMaxNodes; ++node)
			if (g->list[node] != NULL) freeList(g->list[node]);
	}
	g->nbMaxNodes = 0;
	free(g->list);
	return 0;
}

/*int freeGraph(struct Graph g){
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
}*/

/**
* Sauvegarde un graph dans un fichier
 *
 * @param g : Le graph
 * @param filename : Le nom du fichier et son chemin
 * @return : 0 si le graph à bien été exporté
 * @return : EOF si le fichier n'a pas pu être fermé
 */
int saveGraphToFile(struct Graph g, char *filename) {
	char *graph = malloc(g.nbMaxNodes * 1024 * sizeof(char));
	graphToString(g, graph);
	FILE *file = fopen(filename, "w");
	if (fputs(graph, file) == EOF) return -1;
	free(graph);
	return fclose(file);
}

/**
* Charge un graph depuis un fichier
 *
 * @param file : Le fichier contenant le graph
 * @return : Le Graph importé
 */
struct Graph loadGraphFromString(char* file){
	printf("WARNING : Any non-conform file will provoke unspecified behavior");
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
	printf("%s\n",file);
	FILE *f = fopen(file,"r");
	if (!f){
		printf("Error : File not found ! \n");
		return g;
	}
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
	}
	return g;
}

/**
* Converti un graph sous format de caractères pour visualisation
 *
 * @param g : Le graph
 * @param str : La variable de retour contenant le graph au format texte
 */
void graphToString(struct Graph g,char* str){
	int currentIndex = 0;
	char buffnb[16];
	sprintf(buffnb, "%d", g.nbMaxNodes);
	int i = 0;
	struct cchainedList **lists = g.list;
	char comment[50] = "# maximum number of nodes\n";
	memcpy(&str[currentIndex], comment, strlen(comment));
	currentIndex+=strlen(comment);
	while(buffnb[i] != 0){
		str[currentIndex++] = buffnb[i];
		i++;
	}
	str[currentIndex++]='\n';
	strcpy(comment, "# directed\n");
	memcpy(&str[currentIndex], comment, strlen(comment));
	currentIndex+=strlen(comment);
	if (g.isDirected)
		str[currentIndex++]='y';
	else
		str[currentIndex++]='n';
	str[currentIndex++]='\n';
	strcpy(comment, "# node: neighbours\n");
	memcpy(&str[currentIndex], comment, strlen(comment));
	currentIndex+=strlen(comment);
	for (i = 0; i<=g.nbMaxNodes; i++){
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
