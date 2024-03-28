#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Dove str `e una generica stringa e dict `e un vettore di n stringhe distinte. 
Implementare la funzione wrapper solve e scrivere una funzione ricorsiva invocata da
solve che determini se `e possibile costruire str a partire dalle stringhe del dizionario, 
anche ripetute, usando almeno s stringhe diverse del dizionario
*/

// concatena tutte le stringhe e ne verifica la 
int checksol(){

}

// se le prime lunghezze corrispondono con le prime lettere
int checkpromising(){

}

int disp_rip(int n, int pos, char **val, char **sol, int k, int cnt){
    int i;
    if(pos>=k){
        if(checksol()==1){
            printf("s: ");
            for(i=0; i<pos; i++){
                printf("%s ", sol[i]);
            }
        }
        return cnt+1;
    }
    for(i=0; i<n; i++){
        if(checkpromising())
        sol[pos] = strcpy(sol[pos], val[i]);
        cnt = disp_rip(n, pos+1, val, sol, k, cnt);
    }
    return cnt
}

void solve(char *str, char **dict, int n, int s){
    int i=0; char **sol;
    for(i=s; i<n; i++){
        disp_rip(n, 0, dict, sol, i, 0);
    }
}