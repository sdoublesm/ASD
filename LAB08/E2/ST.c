#include "ST.h"

struct symboltable {char **v; int N;};

ST STinit(int maxN){
    ST st; int i;
    st = malloc(sizeof(*st));
    st->v = calloc(MAXN, sizeof(char*));
    for(i=0; i<maxN; i++){
        st->v[i] = calloc(MAXC, sizeof(char));
    }
    st->N = 0;
}

int STsize(ST st){
    return st->N;
}

void STinsert(ST st, char label[MAXC], int index){
    stpcpy(st->v[index], label);
    st->N++;
}

int STgetIndex(ST st, char *name){
    for(int i = 0; i < st->N; i++) {
        if(strcmp(name, st->v[i]) == 0)
            return i;
    }
    return -1;
}

int STsearch(ST st, char *str){
    int i;
    for (i = 0; i  < st->N; i++)
        if (st->v[i]!=NULL && strcmp(str, st->v[i])==0)
            return i;
    return -1;
}
