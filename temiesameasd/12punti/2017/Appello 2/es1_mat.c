#include <stdio.h>


void f(int m1[8][8], int r1, int c1, int m2[6][6], int r2, int c2, int x, int y){
    int i,j;
    int k,t;
    for(i=x,k=0;i<x+r2 && i<r1;i++,k++){
        for(j=y,t=0;j<y+c2 && j<c1;j++,t++){
            m1[i][j]=m2[k][t];
        }
    }
}

int main(){
    int m1[8][8] = {
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1},
    };

    int m2[6][6]={
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
    };

    int r1=8;
    int c1=8;
    int r2=6;
    int c2=6;
    int x=5;
    int y=3;
    f(m1,r1,c1,m2,r2,c2,x,y);
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            printf("%d ",m1[i][j]);
        }
        printf("\n");
    }
    return 0;
}
