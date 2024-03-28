#include <stdio.h>
#include <stdlib.h>


/*
vettore S contenente una sequenza di
somme obiettivo, scrivere una funzione ricorsiva che valuti 
se sia possibile ottenere le somme riportate in S
utilizzando gli elementi del vettore I. Non è necessario usare 
tutti gli elementi di I, ma ogni elemento può
essere usato al massimo una volta. Una volta trovata una soluzione
valida, interrompere la ricerca: non è
necessario individuare tutte le soluzioni possibili.


* Genero le possibili partizioni dell'insieme in m blocchi di dimensione variabile
* e stampo quelle la cui somma è uguale agli elementi di S
*/

int checksol(int n, int k, int *val, int *sol, int *sums){
    int i, j, sum;
    for(i=0; i<k; i++){
        sum=0;
        for(j=0; j<n; j++){
            if(sol[j]==i){
                sum+=val[j];
            }
        }
        if(sum!=sums[i]){
            return 0;
        }
    }
    return 1;
}

// ! - ALGORITMO DI ER
int part_ER(int n, int m, int k, int pos, int *val, int *sol, int *sums, int *found){
    int i, j;
    //condizione di terminazione
    if(pos>=n){
        if(checksol(n, k, val, sol, sums)==1){
            for(i=0; i<k; i++){
                for(j=0; j<n; j++){
                    if(sol[j]==i){
                        printf("+ %d ", val[j]);
                        *found = 1;
                    }
                }
            printf("= %d\n",sums[i]);
            }
        }
    return *found;
    }
    if(*found==0){
        for(i=0; i<m; i++){
            sol[pos] = i;
            part_ER(n, m, k, pos+1, val, sol, sums, found);
        }
        sol[pos] = m;
        part_ER(n, m+1, k, pos+1, val, sol, sums, found);
    }
}

int main(void){
    int I[6] = {1, 2, 3, 4, 5, 6}, 
    S[3] = {1, 7, 7}, 
    dimI = 6, dimS=3, *sol=calloc(dimI, sizeof(int)), f=0;
    f = part_ER(dimI, 0, dimS, 0, I, sol, S, &f);
    if(f==0){
        printf("Non e' possibile ottenere il risultato desiderato.");
    }
    return 0;
}