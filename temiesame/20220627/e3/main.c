#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*
Si vogliono generare tutte le sequenze alfabetiche di k (parametro del programma) 
caratteri che rispettino i seguenti vincoli:
• si possono usare solo lettere minuscole (da ‘a’ a ‘z’) e maiuscole (da ‘A’ a ‘Z’)
• [x] al massimo la metà dei caratteri possono essere lettere minuscole
• [x] lo stesso carattere, senza distinguere tra maiuscolo o minuscolo, 
non può apparire più di p (parametro del programma) volte (era consecutivamente).
*/

int checkpromising(int pos, int n, int p, int k, char *val, char *sol){
    int i, j, lowercnt=0, charcnt;
    for(i=0; i<=pos; i++){
        charcnt = 0;
        if(islower(sol[i])){
            lowercnt++;
        }
        for(j=0; j<=pos; j++){
            if(tolower(sol[i])==tolower(sol[j])){
               charcnt++; 
            }
        }
        if(charcnt>p){
            return 0;
        }
    }
    if(lowercnt>k/2){
        return 0;
    }
    return 1;
}

// disposizioni (con rip) di n elementi in gruppi di k elementii
int disp_rip(int pos, int n, int k, char *val, char *sol, int cnt, int p){
    int i;
    // condizione di terminazione
    if(pos>=k){
        for(i=0; i<k; i++){
            printf("%c ", sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    // ricorsione
    for(i=0; i<n; i++){
        sol[pos]= val[i];
        if(checkpromising(pos, n, p, k, val, sol)==1){
            cnt = disp_rip(pos+1, n, k, val, sol, cnt, p);
        }
         
    }
    return cnt;
}

int main(void){
    char val[52], *sol;
    int i, n = 52, k=3, p=1;
    sol = malloc(n*sizeof(char));
    
    for(i=0; i<26; i++){
        val[i] = 'a' + i;
        val[i+26] = 'A' + i;
    }

    disp_rip(0, n, k, val, sol, 0, p);

    free(sol);
    return 0;
}

