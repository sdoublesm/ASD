#include <stdio.h>
#include <stdlib.h>

void change(int **M, int r, int c){
    int i, j, k;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(M[i][j]%3==0){
                for(k=0; k<r; k++){
                    M[k][j] = 3; 
                } 
                for(k=0; k<c; k++){
                    M[i][k] = 3; 
                }    
            }
        }
    }
}