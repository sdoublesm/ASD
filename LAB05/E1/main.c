#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s;
    int f;
    int d;
} att;

// Esercizio n. 1: Sequenza di attivita'

// esegue il check sul vettore soluzione
// confrontando ogni elemento del vettore sol con quelli di val
int check(int n, att *val, int *sol, int pos) {
    for (int i = 0; i < pos; i++) {
        if (sol[i] == 1 && (val[i].f > val[pos].s && val[i].s < val[pos].f))
            return 0;  // attività incompatibili   
    }
    return 1;
}

// conviene utilizzare modello con dispozizioni ripetute
// e' piu facile manipolare il vettore sol con soli 0 e 1
// per ottenere poi al termine dell'algoritmo ricorsivo
// il vettore di soluzioni cercato
// -> invece che stampare ogni soluzione, la funzione 
// determina di volta in volta se le attivita' della soluzione
// corrente hanno somma della durata massima
// ! ERRORE: solo max deve essere passato by reference!
int powerset(int pos, att *val, int *sol, int n, int cnt, int *solCompl, int sum, int *max) {
    int i;
    if (pos >= n) {
        if(sum>*max){
            *max = sum; // determinazione del massimo
            for (i=0; i<n; i++){
                solCompl[i] = sol[i];
            }  
        }
        return 1;
    }
    sol[pos] = 0;
    cnt = powerset(pos+1, val, sol, n, cnt, solCompl, sum, max);
    if(check(n, val, sol, pos)){ 
        sol[pos] = 1;
        sum += val[pos].d;
        cnt = powerset(pos+1, val, sol, n, cnt, solCompl, sum, max);
    }
    return cnt;
}

// funzione wrapper
int attSel(att *v, int n){
    int *sol, *solCompl, i, max=0;
    sol = malloc(n*sizeof(int));
    solCompl = malloc(n*sizeof(int));
    // riempie il vettore 
    powerset(0, v, sol, n, 0, solCompl, 0, &max);
    printf("\nSequenza risultante: ");
    for(i=0; i<n; i++){
        if(solCompl[i]==1)
            printf("(%d, %d) ", v[i].s, v[i].f);
    }

    free(sol);
    free(solCompl);

    return 0;
}

int main(void){
    att *attivita;
    int i, n;
    FILE *fp_read = fopen("att.txt", "r");
    if(fp_read==NULL){
        printf("Errore durante l'apertura del file.");
        return -1;
    }
    fscanf(fp_read, "%d", &n);
    printf("N: %d\nS: ", n);
    attivita = malloc(n*sizeof(att));
    for(i=0; i<n; i++){
        fscanf(fp_read, "%d %d", &(attivita[i].s), &(attivita[i].f));
        attivita[i].d = attivita[i].f - attivita[i].s;
        printf("(%d, %d) ", attivita[i].s, attivita[i].f);
    }
    attSel(attivita, n);
    fclose(fp_read);
    free(attivita);
    return 0;
}