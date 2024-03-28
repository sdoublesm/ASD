#include <stdio.h>
#include <stdlib.h>

// multi insieme s memorizzato in un vettore val
// s1 e s2 sono due partizioni (quindi sottoinsiemi disgiunti di S)
// tali che la somma degli elementi di S1 è uguale a un valore s 
// + la somma degli elementi di S2. 

int checksol(int n, int m, int *val, int *sol, int s){
    int i, sum1=0, sum2=0;
    for(i=0; i<m; i++){

    }
}

// ! - ALGORITMO DI ER
int part_ER(int n, int m, int pos, int *val, int *sol, int s, int *found){
    int i, j;
    //condizione di terminazione
    if(pos>=n){
        //if(checksol(n, m, val, sol, s)==1){
            for(i=0; i<m; i++){
                for(j=0; j<n; j++){
                    if(sol[j]==i){
                        printf("%d ", val[j]);
                        *found = 1;
                    }
                }
                printf("\n");
            }
            printf("--------\n");
        //}
    return *found;
    }
    //if(*found==0){
        for(i=0; i<m; i++){
            sol[pos] = i;
            part_ER(n, m, pos+1, val, sol, s, found);
        }
        sol[pos] = m;
        part_ER(n, m+1, pos+1, val, sol, s, found);
    //}
}

int main(void){
    int n=8, v[8] = {1, 2, 3, 4, 5, 6, 7, 8}, s = 3, f=0, *sol = malloc(n*sizeof(int)); 
    part_ER(n, 0, 0, v, sol, s, &f);   
    return 0;
}