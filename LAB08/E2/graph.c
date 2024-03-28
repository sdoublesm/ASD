
// Esercizio n.2: Rete di calcolatori 

/*
grafo non orientato e pesato rappresenta una rete di elaboratori 
appartenenti ciascuno ad una sottorete

peso associato ad ogni arco rappresenta il flusso di dati tra due elaboratori della stessa sottorete o di
sottoreti diverse

Il grafo è contenuto in un file, il cui nome è passato come argomento 
sulla linea di comando. Il file è composto da un numero indefinito di righe 
ciascuna delle quali contiene una quaterna di stringhe
alfanumeriche, di al massimo 30 caratteri, e un intero:
<id_elab1> <id_rete1> <id_elab2> <id_rete2> <flusso>

Si scriva un programma in C in grado di caricare in memoria il grafo, 
leggendone i contenuti da file e di potervi effettuare alcune semplici operazioni.
La rappresentazione della struttura dati in memoria deve essere fatta tenendo 
conto dei seguenti vincoli: il grafo sia implementato come ADT di I classe, 
predisposto in modo tale da poter contenere sia la matrice sia le liste 
di adiacenza. Nella fase di caricamento dei dati da file si generi solamente la
matrice di adiacenza, su comando esplicito va generata anche la lista di adiacenza.
si utilizzi una tabella di simboli tale da fornire corrispondenze “da nome a indice” 
e “da indice a nome”.

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GRAPH.h"

// ADT di I classe GRAFO
struct g {int V; int E; int **madj; link head; ST tab;};
// tabella di simboli utilizzata: vettore -> corr. indice - nome (label)
// nel caso utilizzassimo come ST un BST o una tabella di hash
// l’indice del vertice è memorizzato esplicitamente

static int **MATRIXint(int r, int c, int val) {int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i=0; i < r; i++){
        t[i] = malloc(c * sizeof(int));
        for (i=0; i < r; i++){
            for (j=0; j < c; j++){
                t[i][j] = val;
            }
        }
    }
    return t;
}

static edge EDGEcreate(int v, int w, int wt) {
    edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

void GRAPHinsertE(GRAPH G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

GRAPH loadG(FILE *fin){
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    GRAPH G;
    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }
    while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3){
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
        }
    return G;
}

GRAPH GRAPHinit(int V) {
    GRAPH G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(GRAPH G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}