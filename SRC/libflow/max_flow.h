#include <stdbool.h>
#ifndef __STDIO_H
	#define __STDIO_H
	#include <stdio.h>
#endif
#ifndef __STDLIB_H
	#define __STDLIB_H
	#include <stdlib.h>
#endif
#ifndef __STRING_H
	#define __STRING_H
	#include <string.h>
#endif

#include <math.h>

#include "../liblist/list.h"

#include "../libgraph/graph.h"



#ifndef GRAPH_FLOW_H

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y));

struct amel {
	int succes;
	int *chn;
	int *orig;
	int *ec;
	int source;
	int queue;
};


int **floyd_warshall(struct Graph g, int** flot, int source, int puit);
int **djikstra(struct Graph g, int** flot, int source, int puit);
int maj_flot(int F, int** flot, struct Graph g, struct amel chaine_amel);
int flot_max(struct Graph g, int source, int puit, struct amel (*f)(struct Graph, int**,int,int,int** (*f)(struct Graph,int**,int,int)), int** (*f2)(struct Graph,int**,int,int));
struct amel bfsMethod(struct Graph g, int** flot, int source, int puit, int** (*f)(struct Graph,int**,int,int));
struct amel shortestMethod(struct Graph g, int** flot, int source, int puit, int** (*f)(struct Graph,int**,int,int));
int** djikstra(struct Graph g, int** flot, int source, int puit);
int** floyd_warshall(struct Graph g, int** flot, int source, int puit);



#endif