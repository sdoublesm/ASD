#include <stdio.h>
#include <stdlib.h>

// Esercizio 2: Allocazione di matrici

int **malloc2dR(int nr, int nc){
    int **m, i;
    m = malloc(nr*sizeof(int *));
    for(i=0; i<nr; i++){
        m[i] = malloc(nc*sizeof(int));
    }
    return m;
}

void free2d(int **m, int nr){
    int i;
    for(i=0; i<nr; i++){
        free(m[i]);
    }
    free(m);
}

void separa(int **mat, int nr, int nc, int *vb, int *vn){
    int i, j, cb=0, cn=0;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if((i%2==0 && j%2==0) || (i%2!=0 && j%2!=0)){
                vb[cb] = mat[i][j]; cb++;
            }
            if((i%2==0 && j%2!=0) || (i%2!=0 && j%2==0)){
                vn[cn] = mat[i][j]; cn++;
            }
        }
    }

    printf("vb:");
    for(i=0; i<cb; i++){
        printf(" %d", vb[i]);
    }

    printf("\nvn:");
    for(i=0; i<cn; i++){
        printf(" %d", vn[i]);
    }
}

int main(void){
    int nr, nc, i, j, *vb, *vn;
    FILE *fp_read = fopen("mat.txt", "r");

    if(fp_read==NULL){
        printf("Errore nell'apertura del file.");
        return -1;
    }
    
    // si assume che il file sia nel formato corretto
    fscanf(fp_read, "%d %d", &nr, &nc);
    // noti nr e nc, alloco la matrice
    int **matrix = malloc2dR(nr, nc);
    
    printf("matrix:\n");
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            fscanf(fp_read, "%d", &matrix[i][j]);
            printf("[%d][%d]: %d\n", i, j, matrix[i][j]);
        }       
    }

    vb = malloc((nr*nc/2)*sizeof(int));
    vn = malloc((nr*nc/2)*sizeof(int));

    separa(matrix, nr, nc, vb, vn);

    free2d(matrix, nr);
    free(vb);
    free(vn);
    fclose(fp_read);

    return 0;
}