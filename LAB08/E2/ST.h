#ifndef ST_H
#define ST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXC 30
#define MAXN 100

typedef struct symboltable *ST;

ST STinit(int maxN);
int STsize(ST st);
void STinsert(ST st, char label[MAXC], int index);
int STgetIndex(ST st, char *name);
int STsearch(ST st, char *str);
void STfree(ST st);

#endif