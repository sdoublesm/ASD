#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

#define N_cmds 7
#define DBG 0

void printMenu(char *cmds[], int *choice){
    int i;
    printf("------------------ cmds\n");
    for(i=0;i<N_cmds;i++)
        printf("%2d | %s\n",i,cmds[i]);
    printf("Inserisci codice comando: ");
    scanf(" %d",choice); printf("\n");
}

int main(int argc, char **argv) {
    char *cmds[] = {"esci", "stampa personaggi", "stampa inventario", "cerca personaggio", "aggiungi personaggio", "elimina personaggio", "modifica equipaggiamento"};
    char codetosearch[LEN];
    int choice, end=0;
    FILE *fp_read;

    pgList_t pgList = pgList_init();
    invArray_t invArray = invArray_init();
    pg_t *pgp, pg;

    fp_read = fopen("pg.txt","r");
    pgList_read(fp_read, pgList);
    fclose(fp_read);
    fp_read = fopen("inventario.txt","r");
    invArray_read(fp_read, invArray);
    fclose(fp_read);

    do {
        printMenu(cmds, &choice);
        switch(choice){

            case 0: {
                end = 1;
            } break;

            case 1: {
                pgList_print(stdout, pgList, invArray);
            } break;

            case 2: {
                invArray_print(stdout, invArray);
            } break;

            case 3: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codetosearch);
                pgp = pgList_searchByCode(pgList, codetosearch);
                if (pgp!=NULL) {
                    pg_print(stdout, pgp, invArray);
                }
            } break;

            case 4: {
                printf("CODE NAME CLASS HP MP ATK DEF MAG SPR: ");
                if (pg_read(stdin, &pg) != 0) {
                    pgList_insert(pgList, pg);
                }
            } break;

            case 5: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codetosearch);
                pgList_remove(pgList, codetosearch);
            } break;

            case 6: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codetosearch);
                pgp = pgList_searchByCode(pgList, codetosearch);
                if (pgp!=NULL) {
                    pg_updateEquip(pgp, invArray);
                }
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!end);

    pgList_free(pgList);

    return 0;
}