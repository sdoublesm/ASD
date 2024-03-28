#include <stdio.h>
#include <stdlib.h>
/*
Una matrice M quadrata di dimensione N x N rappresenta le relazioni 
di amicizia tra N persone. Ogni cella contenente il valore 1 indica che 
la coppia (i,j) è una coppia di amici. In caso contrario il valore
memorizzato è 0. La relazione di amicizia è simmetrica (se i considera j 
suo amico, vale anche l'opposto). Si scriva una funzione ricorsiva in grado 
di suddividere le persone nel minor numero di gruppi possibili facendo 
in modo che tutte le persone in un gruppo siano mutualmente amiche. È ammesso
che ci siano gruppi composti da una singola persona
*/

// g è l'indice corrente del gruppo
int checkpromising(int pos, int g, int *val, int *sol, int M[4][4]){
    int i, j; 
    for(i=0; i<pos; i++){
        if(sol[i]==g){
            for(j=0; j<pos; j++){
                if(sol[j]==g && val[i]!=val[j] && M[i][j]==0){
                    return 0;
                }
            }
        }
    }
    return 1;
}


// sol all'indice j indica il numero del gruppo a cui appaartiene val[j]
void part_ER(int pos, int n, int m, int k, int *val, int *sol, int M[4][4], int *found){
    int i, j;
    // condizione di terminazione
    if(pos>=n){
        if(m==k){
            for(i=0; i<k; i++){
                for(j=0; j<n; j++){
                    if(sol[j]==i){
                        printf("%d ", val[j]);
                        *found = 1;
                    }
                }
                printf("\n");
            }
            printf("------\n");
            printf("k: %d", k);
        }
    return;
    }
    
    if(*found==0){
        for(i=0; i<m; i++){
            if(checkpromising(pos, i, val, sol, M)==1){
                sol[pos] = i;
                part_ER(pos+1, n, m, k, val, sol, M, found);
            }
        }
        if(checkpromising(pos, i, val, sol, M)==1){
            sol[pos]=m;
            part_ER(pos+1, n, m+1, k, val, sol, M, found);
        }
    }
}

void parts(int M[4][4], int n){
    int found=0, k, i, *val, *sol;
    val = malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        val[i] = i;
    }
    sol = calloc(n, sizeof(int));
    for(k=0; k<n && found==0; k++){
        part_ER(0, n, 0, k, val, sol, M, &found);
    }

    free(val);
    free(sol);

}

int main(void) {
    int n=4, M[4][4] = {{1, 1, 0, 1}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 0, 1}};

    // Stampa della matrice M'
    printf("Matrice M:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    parts(M, n);

    return 0;
}