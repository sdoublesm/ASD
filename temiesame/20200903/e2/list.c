
/*
Si definisca una struttura dati adatta a rappresentare una lista linkata circolare. In
una lista circolare il puntatore al successore dell’elemento in coda punta all’elemento
di testa della lista stessa. I nodi della lista siano caratterizzati da un valore intero e
da un contatore di occorrenze. Si definisca la lista come ADT di I classe e il tipo nodo
come quasi ADT. Indicare esplicitamente in quale modulo/file appare la definizione
dei tipi proposti. Non e' ammesso l’uso di funzioni di libreria. 
Si implementi la seguente funzione di inserimento nella lista definita in precedenza: se l’elemento e'
gia' presente, si incrementa il contatore. Se non e' presente va inserito nella posizione
indicata dal secondo parametro. La testa ha posizione 0 per convenzione. Non e'
ammesso l’uso di funzioni di libreria.
! > void LISTinsert(list_t L, int posizione, ...)
*/

// --------------- list.h
#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;
struct node{
    int val, occ;
    link next;
};
typedef struct list_t *LIST;
#endif

// --------------- list.c

struct list_t{
    link head, tail;
    int N;
};

void LISTinsert(LIST L, link toinsert, int pos){
    link x, tmp=malloc(sizeof(*tmp)); int p=0;
    for(x=L->head; p<L->N; x=x->next, p++){
        if(pos%L->N==((p+1)%L->N)){
            if(x->next->val==toinsert->val){
                x->next->occ++;
            }
            else{
                tmp = x->next->next;
                x->next = toinsert;
                x->next->next = tmp;
            }
            L->N++;
        }
    }
}

