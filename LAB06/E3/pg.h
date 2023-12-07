#include "inventario.h"

typedef struct {
    int using;
    obj **vettEq;
} eq;

typedef struct {
    char code[7];
    char name[50];
    char class[50];
    eq *equip;
    stat stats;
} PG;

typedef struct node *link;

struct node {
    PG val;
    link next;
};

typedef struct {
    link headPG;
    link tailPG;
    int nPG;
} tabPG;

link newNode(PG val, link next);
link listInsHead(link h, PG val);
void listInsCoda(link *hp, link *tp, PG val);
link searchByCode(link h);
PG *addObj(tabPG *tabPers, tabObj *inv);
PG *removeObj(tabPG *tabPers);
void printPG(PG personaggio);
void printList(link h);
tabPG *insPG(tabPG *tabPers);
tabPG *delCodice(tabPG *tabPers);
tabPG *loadPGs(char *filename);
void printStats(stat stats);
obj *searchObj(tabObj *inv, char *objname);

int main(void);
