#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"
#include "list.h"

typedef struct e {int v; int w; int wt;} edge;
typedef struct g *GRAPH;

void GRAPHinsertE(GRAPH G, int id1, int id2, int wt);

GRAPH loadG(FILE *fin);
GRAPH initG(int V);
void freeG(GRAPH G);

#endif