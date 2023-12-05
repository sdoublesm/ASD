#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s {
    int hp, mp, atk, def, mag, spr;
} stat;

typedef struct o {
    char name[50];
    char type[50];
    stat stats;
} obj;

typedef struct t {
    obj *vettObjs;
    int nObjs;
    int maxObjs;
} tabObj;

char * strtolower(char tolow[50]);
void printStats(stat stats);
void printOD(obj o);
obj *searchObj(tabObj *inv, char tosearch[50]);
tabObj *loadObjects(char *filename);

#endif // INVENTARIO_H