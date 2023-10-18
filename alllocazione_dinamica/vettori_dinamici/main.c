#include <stdio.h>
#include <stdlib.h>
// inverti ordine con riallocazione (con raddoppio)

int main(void){
    float *v, d; int N, MAXN=1, i;
    // allocazione iniziale
    v = (float *) malloc(N*(sizeof (float)));
    
    printf("Inserisci elementi\n");
    printf("Elemento 0: ");
    while (scanf("%f", &d)>0){
        // i vuole andare fuori dal vettore attuale?
        if(i==MAXN){ // segnala la fine dei dati -> va riallocato

        MAXN = MAXN*2; // invece che incrementarla, si moltiplica per un fattore
        
        v = realloc(v, MAXN*sizeof(float));
        }
        v[i++] = d;
        printf("Elemento %d", i);
    }
    printf("Dati in ordine inverso\n");
    for (i=N-1; i>=0; i--)
        printf("El. %d: %f\n", i, v[i]);
    free(v);

    return 0;
}