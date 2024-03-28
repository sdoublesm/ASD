#include <stdio.h>
#include <stdlib.h>

void f(int M[3][3], int r, int c, int ***newM){
    int i, j, k, z, sum;
    *newM = calloc(r, sizeof(int*));
    for(i=0; i<r; i++){
        (*newM)[i] = calloc(c, sizeof(int));
    }

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            for(k=i, z=j; k<r && z<c; k++, z++){
                (*newM)[i][j] += M[k][z];
                
            }
        }
    }

}

int main(void){
    int r = 3, c = 3, M[3][3]= {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, **newmatrix;
    f(M, r, c, &newmatrix);
        // Stampa della matrice M'
    printf("Matrice M':\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", newmatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}