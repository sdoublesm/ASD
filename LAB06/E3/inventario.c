
/*
TODO [Modulo dell'inventario] deve:
* Acquisire da file info relative agli oggetti disponibili, mantenendo la
* struttura VETTORE DI STRUCT
* ricerca di un oggetto per name
* stampa dei dettagli di un oggetto

- numero O di oggetti
- sulle O righe successive appaiono i dettagli di ogni oggetto disponibile
* ogni oggetto è caratterizzato da un name, una tipologia 
* e da una sestupla a rappresentare i modificatori alle statistiche base
* di un personaggio 
- il name e la tipologia sono rappresentati da una stringa, 
- priva di spazi, di massimo 50 caratteri alfabetici (maiuscoli o minuscoli) 
- i modificatori alle statistiche sono dei numeri interi (potenzialmente anche negativi), 
quindi possono essere visti come bonus (se positivi) o malus (se negativi). 

*/

#include "inventario.h"

char * strtolower(char tolow[50]){
    char *s; s = malloc(50*sizeof(char));
    strcpy(s, tolow);
    for(int i=0;s[i]!='\0';i++){
        s[i]=tolower(s[i]);
    }
    return s;
}

void printStats(stat stats){
    printf("|- HP: %d\n|- MP: %d\n|- ATK: %d\n|- DEF: %d\n|- MAG: %d\n|- SPR: %d\n",
    stats.hp, stats.mp, stats.atk, stats.def, stats.mag, stats.spr);
}

// Stampa dettagli di un oggetto
void printOD(obj o){
    printf("name: %s\ntype: %s\n", o.name, o.type);
    printStats(o.stats);
    printf("------------------------------\n");
}

obj *searchObj(tabObj *inv, char tosearch[50]){
    int found=0;
    printf("\nRisultati della ricerca lineare per %s:\n", tosearch);
    for(int i=0;i<inv->nObjs;i++){
        if(strncmp(strtolower(tosearch), strtolower(inv->vettObjs[i].name), strlen(tosearch))==0){
            found = 1;
            //printOD(inv->vettObjs[i]);
            return &(inv->vettObjs[i]);
        }
    }
    if (found==0)
        printf("Nessun risultato.\n");
        return NULL;
}

tabObj *loadObjects(char *filename){
    int n, i;
    FILE *fp_read = fopen(filename, "r");
    if (fp_read == NULL) {
        printf("Errore nell'apertura del file");
        return NULL;
    }

    tabObj *tabInv = malloc(sizeof(tabObj));
    fscanf(fp_read, "%d", &n);
    tabInv->nObjs = n;
    tabInv->vettObjs = malloc(n * sizeof(obj));
    tabInv->maxObjs = 8;
    for (i = 0; i < n; i++) {
        fscanf(fp_read, "%s %s %d %d %d %d %d %d",
        tabInv->vettObjs[i].name, tabInv->vettObjs[i].type,
        &(tabInv->vettObjs[i].stats.hp), &(tabInv->vettObjs[i].stats.mp),
        &(tabInv->vettObjs[i].stats.atk), &(tabInv->vettObjs[i].stats.def),
        &(tabInv->vettObjs[i].stats.mag), &(tabInv->vettObjs[i].stats.spr));
        // printOD(tabInv->vettObjs[i]);
    }
    fclose(fp_read);
    printf("Inventario caricato correttamente da '%s'.\n", filename);
    return tabInv;
}