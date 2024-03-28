#include <stdio.h>
#include <stdlib.h>

/*
Dato un vettore V di interi positivi, di dimensione nota d, 
identificare se possibile un modo di
suddividerne il contenuto in x sottoinsiemi, 
con x parametro del problema, tale per cui la somma di
tutti gli elementi di ognuno dei sottoinsiemi sia la stessa. 
Ogni elemento del vettore deve essere
assegnato a un singolo sottoinsieme.
La ricerca, in caso di successo, deve terminare alla 
prima soluzione valida trovata.
*/

/*
Bisogna ricorrere alle partizioni dell'insieme di partenza in x blocchi
-> ALGORITMO DI ER permette di trovare
o tutte le partizioni di n oggetti memorizzati nel
vettore val in k blocchi con k variabile tra 1 e n
o una partizione in k blocchi.

indice pos per scorrere gli n oggetti e terminare la
ricorsione quando pos >= n
indice i per scorrere gli m blocchi utilizzabili in quel
passo
vettore sol di n elementi per la soluzione
*/

int checksol(int n, int k, int *val, int *sol){
    int sum=0, csum=0, i, j;
    // devo controllare che tutti gli elementi appartenenti agli stessi blocchi
    // abbiano la stessa somma, se ciò accade, sol è accettabile
    for(i=0; i<=k; i++){
        if(csum!=sum){
            return 0;
        }
        sum=0;
        for(j=0; j<n; j++){
           if(sol[j]==i){
                sum += val[j];
           }
        }
        if(i==0)
            csum = sum;
    }
    return 1;
}

// ! - ALGORITMO DI ER
void SP_rec(int n, int m, int k, int pos, int *val, int *sol, int *found){
    int i, j, stop=0;
    //condizione di terminazione
    if(pos>=n){
        if(m==k){
            if(checksol(n, k, val, sol)==1){
                for(i=0; i<m; i++){
                    for(j=0; j<n; j++){
                        if(sol[j]==i){
                            printf("%d ", val[j]);
                            *found = 1;
                        }
                    }
                printf("\n");
                }
            }
        }
    return;
    }

    if(*found==0){
        for(i=0; i<m; i++){
            sol[pos] = i;
            SP_rec(n, m, k, pos+1, val, sol, found);
        }
        sol[pos] = m;
        SP_rec(n, m+1, k, pos+1, val, sol, found);
    }
}


int main(void){
    int d=11, v[11] = {2, 0, 4, 6, 5, 4, 3, 2, 0, 4, 2}, *sol, x=4, f=0;
    sol = malloc(d*sizeof(int));
    printf("Partizione del vettore di %d elementi in %d gruppi con somme uguali:\n", d, x);
    SP_rec(d, 0, x, 0, v, sol, &f); 
    return 0;
}