#include <stdio.h>
#include <stdlib.h>

int counter(int *a, int val, int l, int r) {
    int c = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == val) 
            c++;
    }
    return c;
}

int majority(int *a, int l, int r) {
    if (l == r) 
        return a[l];
    
    int m = (r-l)/2+l;
    int majL = majority(a, l, m);
    int majR = majority(a, m + 1, r);

    if (counter(a, majL, l, r)>(r-l+1)/2)
        return majL;
    
    if (counter(a, majR, l, r)>(r-l+1)/2) 
        return majR;

    return -1;
}

int main(void) {
    int N, *v, maj;
    printf("---- Ricerca ricorsiva dell'elemento maggioritario di un vettore\n");
    printf("> Inserisci la dimensione del vettore: ");
    scanf("%d", &N);
    v = malloc(N * sizeof(int));
    printf("> Inserisci il vettore in un'unica riga: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }
    maj = majority(v, 0, N - 1);
    if (maj != -1) {
        printf("Elemento maggioritario: %d", maj);
    } else {
        printf("Nessun elemento maggioritario.");
    }
    free(v);
    return 0;
}