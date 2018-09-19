

#ifndef TP2GRAPH_GRAPH_H
#define TP2GRAPH_GRAPH_H

struct Neighbour {
	int neighbour;
	int weight;
	Neighbour nextNeighbour;
	Neighbour previousNeighbour;
};

struct Graph{
	bool isDirected;
	int nbMaxNodes;
	Neighbour *adjList;
};

#endif //TP2GRAPH_GRAPH_H
