#include <stdio.h>
#include <stdlib.h>

/*
Una macchina industriale può produrre pezzi di diversi tipi, ognuno caratterizzato da un valore e
da un tempo di produzione, valori interi e positivi.
Si assuma per comodità che i vari tipi di pezzi siano univocamente identificati da un singolo intero
nell'intervallo 0 .. P-1.
Ricevuto in input un tempo T e un valore obiettivo V, entrambi interi e positivi, identificare quanti
pezzi di ogni tipo sia possibile produrre entro il tempo T per minimizzare la differenza, in valore
assoluto, tra V e la somma dei valori dei pezzi prodotti, ossia per avvicinarsi il più possibile
all'obiettivo.

? QUANTI PEZZI DI OGNI TIPO E POSSIBILE PRODURRE ENTRO IL TEMPO T PER 
? MINIMIZZARE LA DIFFERENZA TRA V E LA SOMMA DI VALORI DEI PEZZI PRODOTTI
*/

// PRUNING: la somma dei valori nel vettore soluzione deve essere minore di T + 
// ABS(V-sum) deve essere minimo

int calcsum(int *sol, int pos){
    int sum=0;
    for(int i=0; i<pos; i++)
        sum+=sol[i];
    return sum;
}

// disposizioni con ripetizione: dispongo n oggetti in gruppi di k elementi anche ripetuti
// non conta l'ordine
int **disp_rip(int n, int k, int *val, int **sol, int pos, int cnt, int T, int V, int *cmin, int *kmin){
    int i, s;
    if(pos>=k){
        s = calcsum(*sol, pos);
        if(abs(V-s)<*cmin){
            *cmin=abs(V-s);
            *kmin = k;
        }
        return sol;
    }
    for(i=0; i<n; i++){
        (*sol)[pos] = val[i];
        if(calcsum(*sol, pos)<T){
            disp_rip(n, k, val, sol, pos+1, cnt, T, V, cmin, kmin);
        }
    }
    return sol;
}

void produce(int p, int *val, int T, int V){
    int k, i, *sol=calloc(p, sizeof(int)), cmin=V, kmin=0; 
    for(int k=0; k<p; k++){
        disp_rip(p, k, val, &sol, 0, 0, T, V, &cmin, &kmin);
    }
    printf("kmin: %d", kmin);
    free(sol);
}

int main(void){
    int p=8, v[8]={0, 1, 2, 3, 5, 6, 7}, T=19, V=16;
    printf("p: %d\nT: %d\nV: %d\n", p, T, V);
    produce(p, v, T, V);
    return 0;
}