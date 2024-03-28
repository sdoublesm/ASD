#include <stdio.h>
#include <stdlib.h>

void f(int M[3][3], int r, int c, int ***newM, int *newr, int *newc) {
    int i, j, *vr = calloc(r, sizeof(int)), *vc = calloc(c, sizeof(int)), newi = 0, newj = 0;
    *newc = c;
    *newr = r;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (M[i][j] == 0) {
                if (vr[i] != -1) {
                    (*newr)--;
                    vr[i] = -1;
                }
                if (vc[j] != -1) {
                    (*newc)--;
                    vc[j] = -1;
                }
            }
        }
    }

    *newM = (int **)calloc(*newr, sizeof(int *));
    for (i = 0; i < *newr; i++) {
        (*newM)[i] = (int *)calloc(*newc, sizeof(int));
    }

    for (i = 0; i < r; i++) {
        if (vr[i] != -1) {
            for (j = 0; j < c; j++) {
                if (vc[j] != -1) {
                    (*newM)[newi][newj] = M[i][j];
                    newj++;
                }
            }
            newi++;
            newj = 0;
        }
    }
}

int main(void) {
    int r = 3, c = 3, M[3][3] = {{1, 0, 3}, {4, 5, 6}, {7, 8, 9}}, **newmatrix, newr, newc;
    f(M, r, c, &newmatrix, &newr, &newc);

    // Stampa della matrice M'
    printf("Matrice M':\n");
    for (int i = 0; i < newr; i++) {
        for (int j = 0; j < newc; j++) {
            printf("%d ", newmatrix[i][j]);
        }
        printf("\n");
    }

    // Libera la memoria allocata per la nuova matrice
    for (int i = 0; i < newr; i++) {
        free(newmatrix[i]);
    }
    free(newmatrix);

    return 0;
}
