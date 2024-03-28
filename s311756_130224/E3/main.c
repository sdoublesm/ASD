#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXL 100

int isVocale(char c) {
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;
    return 0;
}

int checksol(char **sol, int p, char **res) {
    int len = 0;
    for (int i = 0; i < p-1; i++) {
        if (isVocale(sol[i][strlen(sol[i]) - 1]) == isVocale(sol[i+1][0])) {
            return 0;
        }
        len += strlen(sol[i]);
        strcat(*res, sol[i]);
    }
    len += strlen(sol[p-1]);  
    strcat(*res, sol[p-1]);

    return len;
}

char *generate(int n, int pos, char **item, char **sol, int start, char **res, int *maxlen) {
    if (start >= n) {
        char *currstr=malloc(MAXL*sizeof(char)); *currstr = '\0';
        int currlen = checksol(sol, pos, &currstr);
        if(currlen!=0){
            if (currlen > *maxlen) {
                *maxlen = currlen;
                strcpy(*res, currstr);
            }
        }
        free(currstr);
        return *res;
    }

    for (int i = start; i < n; i++) {
        strcpy(sol[pos], item[i]);
        generate(n, pos + 1, item, sol, i + 1, res, maxlen);
    }
    return generate(n, pos + 1, item, sol, n, res, maxlen);
}

void bestConcat(char **parole, int nparole) {
    int maxlen = 0;
    char *res = malloc(MAXL*sizeof(char)); *res = '\0';
    char **sol = malloc(nparole * sizeof(char *));
    for (int i = 0; i < nparole; i++) {
        sol[i] = malloc(20 * sizeof(char));
    }
    generate(nparole, 0, parole, sol, 0, &res, &maxlen);
    printf("Lunghezza massima: %d\nParola risultante: %s\n", maxlen, res);
    // free elementi di sol
    for (int i = 0; i < nparole; i++) {
        free(sol[i]);
    }
    free(sol);
}

int main(void) {
    char *parole[] = {"abraca", "odabro", "basop", "lula", "acotrop"};
    bestConcat(parole, 5);
    return 0;
}