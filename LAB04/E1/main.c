#include <stdio.h>
#include <stdlib.h>
#define FILENAME "grafo2.txt"

// Esercizio n.1: Vertex Cover

// un vertex cover è un sottoinsieme dei vertici tale che tutti gli archi 
// abbiano almeno uno dei vertici al suo interno

// un vertex cover deve contenere elementi che compaiano in tutti gli archi

// idea di base: generare l'insieme delle parti dell'insieme dei vertici del grafo
// aggiungere verifica che essi siano vertex cover e, nel caso, stamparli.

int check(int pos, int *sol, int **a, int E) {
    int covered;
    
    // se il sottoinsieme e' vuoto restituisce 0
    if(pos==0)
        return 0;
    
    // esegue il controllo sugli archi del 'papabile' vertex cover
    for (int i = 0; i < E; i++) {
        covered = 0;
        // verifica che almeno un elemento nel sottoinsieme copra l'arco
        for (int j = 0; j < pos && !covered; j++) {
            if(sol[j] == a[i][0] || sol[j] == a[i][1]){
                covered = 1;
            }
        }
        // se l'arco non è coperto restituisce 0
        if (!covered) 
            return 0;
    }
    // se tutti gli archi sono coperti restituisce 1
    return covered;
}

// funzione che sfrutta il paradigma 'divide et impera' operando ricorsivamente
// poco intuitivo
// RISCRIVERE CON DISPOSIZIONI RIPETUTE 
int powerset(int pos, int *val, int *sol, int n, int start, int count, int **archi, int E) {
   int i;
   // terminazione -> non ci sono piu elementi
    if (start >= n) {
        // [+] CONDIZIONE -> Controllo che gli elementi in sol fino a pos siano contenuti in tutti gli archi
        if(check(pos, sol, archi, E)==1){
            printf("- { ");
            for (i = 0; i < pos; i++)
                printf("%d ", sol[i]);
            printf("} \n");
        }
        return count+1;  
    }    

   // per tutti gli elementi da start in poi
   for (i = start; i < n; i++) {
      sol[pos] = val[i]; // includi elemento
      count = powerset(pos+1, val, sol, n, i+1, count, archi, E);
   }
   // non aggiunge nulla
   count = powerset(pos, val, sol, n, n, count, archi, E);
   return count;
}

int main(void){
    FILE *fp_read=fopen(FILENAME, "r");
    int N, E, i, *v, *sol, **archi;

    if(fp_read==NULL){
        printf("Errore durante l'apertura del file."); 
        return -1; 
    }

    printf("File '%s' caricato.\n", FILENAME);
    // nella prima riga del file compaiono N (numero di vertici) ed E (numero di archi)
    fscanf(fp_read, "%d %d", &N, &E);
    printf("N: %d | E: %d\n", N, E);
    v = malloc(N*sizeof(int));
    sol = calloc(N, sizeof(int));
    
    printf("Vettore: ");
    // genera vettore contentente i vertici
    for(i=0; i<N; i++){
        v[i] = i;
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Archi letti: ");
    archi = malloc(E*sizeof(int *));
    for(i=0; i<E; i++){
        archi[i] = malloc(2*sizeof(int));
        fscanf(fp_read, "%d %d", &archi[i][0], &archi[i][1]);
        printf("(%d, %d) ", archi[i][0], archi[i][1]);
    }

    printf("\nElenco di tutti i possibili vertex cover:\n");
    powerset(0, v, sol, N, 0, 0, archi, E);
        
    free(v);
    free(sol);
    for(i=0; i<E; i++){
        free(archi[i]);
    }
    free(archi);
    fclose(fp_read);
    return 0;
}