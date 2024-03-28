// ------------------------------------ list.h

#ifndef LIST_H
#define LIST_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ST.h"

#define MAXCL 50
typedef struct el {int v; int w; int wt;} edge_l;
typedef struct list *LIST;
typedef struct node *link;
struct node {int v; int wt; link next;};

LIST LISTinit(int V);
void LISTfree(LIST L);
void LISTinsertL(LIST L, int id1, int id2, int wt);
void LISTedges(LIST G, edge_l *a);
void STinsertWrapper(LIST L,char *name, char *subnet);
void LISTcheckADJ(LIST L);
#endif

// -------------------------------------------