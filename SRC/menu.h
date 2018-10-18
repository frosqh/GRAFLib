#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgraph/graph.h"

#ifndef TP2GRAPH_MENU_H
#define TP2GRAPH_MENU_H

char val[50] = "";
char val2[50] = "";

struct Graph g;

void menu();

void displayMenu();

int addEdgeDispError(struct Graph g, int start, int end, int weight);

#endif //TP2GRAPH_MENU_H
