/*
Sia dato un set di N oggetti, numerati da 1 a N. Ogni oggetto `e caratterizzato da
un suo nome e da una quaterna di interi positivi o nulli: costo, valore, tipo,
quantita. Si scriva una funzione ricorsiva in grado di identificare un insieme di
oggetti tale da rispettare i seguenti vincoli:
• Costo complessivo al piu C, dove C e un intero passato come parametro
• Insieme composto solo da oggetti tipologie diverse
• Si termini l’esecuzione non appena trovata una soluzione valida


! int solve_r(item_t *v, int n, int *sol, int pos, int tot_c, int tot_v, ...);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct i {
    char name[50];
    int costo, tipo, q;
} item_t;

// manca controllo su tipologie tutte diverse
int promising(item_t *sol, int pos, int C){
    int sumc=0, f;
    for(int i=0; i<pos; i++){
        sumc+=sol[i].costo;
    }
    if(sumc<C){
        return 1;
    }
    return 0;
}

int powerset(int n, int pos, item_t *val, item_t *sol, int tot_c, int tot_v, int start, int cnt, int C){
    int i;
    if(start>=n){
        for(i=0; i<n; i++){
            printf("%d", sol[i].name);
        }
        return cnt+1;
    }

    for(i=start; i<n; i++){
        if(promising(sol, pos, C)==1){
            sol[pos] = val[i];
            cnt = powerset(n, pos+1, val, sol, i+1, cnt, tot_c, tot_v, C);
        }
    }
    cnt = powerset(n, pos, val, sol, n, cnt, tot_c, tot_v, C);
    return cnt;
}