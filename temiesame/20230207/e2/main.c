/*
Si scriva una funzione wrapper int f(T t) (e la relativa funzione ricorsiva) che 
ricevuto in input un albero n-ario di interi t di tipo T conti la lunghezza del cammino 
più lungo contenente solo valori positivi o nulli. Fornire la definizione del tipo T e del
tipo nodo al suo intero, come ADT di prima classe e come quasi ADT rispettivamente, 
indicando esplicitamente la divisione in moduli adottata. Per rappresentare l'albero richiesto, 
ogni nodo tiene traccia dei figli mediante un vettore di puntatori a nodo e il numero di figli.
*/

// --------------------------- tree.h
#include <stdio.h>
#include <stdlib.h>

/*
- c_val per il valore corrente (c = current)
- c_cap per la capacità usata correntemente
- b_val valore ottimo corrente
*/


typedef int Item;
typedef struct tree *T;
typedef struct node *link;
struct node {
    Item val;
    link *children;
    int nc;
};

int f(T t);

// --------------------------- tree.c

struct tree {
    link root;
    link z; // nodo sentinella
};

int f(T t){
    int maxlen = 0, currlen=0;
    maxPath(t->root, currlen, &maxlen);
    return maxlen;
}

void maxPath(link root, int curr, int *max){
    //condizione di terminazione
    if(root->nc==0){
        // controllo ottimalita
        if (curr > *max){
            *max = curr;
        }
        return;
    }
    for(int i=0; i<root->nc; i++){
        maxPath(root->children[i], curr+1, max);
    }
    return;
}