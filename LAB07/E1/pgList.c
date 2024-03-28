#include "pgList.h"

typedef struct node *link;

struct node{
    pg_t pers;
    link next;
};

struct pgList_s {
    link head;
    int n;
};

pgList_t pgList_init(){
    pgList_t list=malloc(sizeof(* list));
    list->head=NULL;
    list->n=0;
    return list;
}

void pgList_read(FILE *fin, pgList_t pgList){
    pg_t pers;
    while(pg_read(fin,&(pers))){
        pgList_insert(pgList,pers);
    }
}

void pgList_insert(pgList_t pgList, pg_t pg) {
    link toAdd = malloc(sizeof(struct node));
    toAdd->pers = pg;
    toAdd->next = pgList->head;
    pgList->head = toAdd;
    pgList->n++;
}

void pgList_print(FILE *fin, pgList_t pgList, invArray_t invArray){
    link p;
    for(p = pgList->head; p != NULL; p = p->next) {
        pg_print(fin, &(p->pers), invArray);
    }
    fprintf(fin, "Numero personaggi: %d\n\n", pgList->n);
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link p;
    for(p = pgList->head; p != NULL; p = p->next) {
        if(strcmp(p->pers.cod,cod) == 0) {
            return &(p->pers);
        }
    }
    printf("Personaggio non trovato.\n");

    return NULL;
}

void pgList_free(pgList_t pgList) {
    link p,q;
    for(p = pgList->head; p != NULL; p = q) {
        pg_clean(&(p->pers));
        q = p->next;

        free(p);
    }
    if(pgList != NULL)
        free(pgList);
}

void pgList_remove(pgList_t pgList, char* cod) {
    link p,q;

    //eliminazione primo elemento se lo becco al primo posto
    if(strcmp(pgList->head->pers.cod,cod) == 0) {
        pg_clean(&(pgList->head->pers));
        q = pgList->head;
        free(q);
        pgList->head = pgList->head->next;
        return;
    }

    for(p = pgList->head; p != NULL; q = p, p = p->next) {
        if(strcmp(p->pers.cod,cod) == 0) {
            pg_print(stdout,&(p->pers),NULL);
            q->next = p->next;
            pg_clean(&(p->pers));
            free(p);
            return;
        }
    }
    printf("Personaggio non trovato.\n");
}