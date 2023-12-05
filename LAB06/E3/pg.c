/*
! il modulo dei personaggi e' client del modulo dell'inventario
TODO [Modulo personaggi] deve fornire le funzionalità di:
* [x] acquisizione da file delle informazioni dei personaggi, 
* mantenendo la medesima struttura a lista richiesta nel laboratorio precedente
* [x] inserimento/cancellazione di un personaggio
* [x] ricerca per codice di un personaggio
* [x] stampa dei dettagli di un personaggio e del relativo equipaggiamento, se presente 
* [ ] modifica dell’equipaggiamento di un personaggio, ovvero aggiunta/rimozione di un oggetto
*/

#include "inventario.h"
#include "pg.h"

// ------- FUNZIONI GESTIONE LISTA

// riceve come parametri cio che si vuole inserire e restituisce il puntatore al nodo
link newNode(PG val, link next){
    link x = malloc(sizeof(struct node));
    if (x==NULL) // controllo errore
        return NULL; 
    else{
        x->val = val;
        x->next = next;
    }
    return x;
}

// INSERZIONE IN TESTA
link listInsHead(link h, PG val){
    h = newNode(val, h);
    return h;
}

// INSERZIONE IN CODA (algoritmo meno complesso)
void listInsCoda(link *hp, link *tp, PG val){
    if (*hp == NULL) {
        *hp = *tp = newNode(val, NULL);
    } else {
        (*tp)->next = newNode(val, NULL);
        *tp = (*tp)->next;
    }
}

// Il codice e' univoco, ci sara' al massimo solo un risultato
link searchByCode(link h){
    link x;
    char code[7];
    printf("Inserisci il codice di 6 caratteri da cercare:\n");
    scanf("%s", code); getchar();
    printf("Risultato della ricerca:\n");
    for(x=h; x!=NULL && strcmp(x->val.code, code)!=0; x=x->next);
    if(x==NULL){
        printf("Nessun risultato.\n");
        return NULL;        
    }
    printf("----- %s\nNome: %s\nClasse: %s\n", 
    x->val.code, x->val.name, x->val.class); 
    return x;  
}

// ------- FUNZIONI GESTIONE PERSONAGGI

// GESTIONE EQUIPAGGIAMENTO

// funzione stampa equipaggiamento

PG *addObj(PG *personaggio, tabObj *inv){
    char objname[50];
    obj *object;
    printf("AGGIUNTA DI UN ELEMENTO ALL'EQUIPAGGIAMENTO\n");
    if(personaggio->equip->using >= 8){
        printf("L'equipaggiamento del personaggio %s e' al completo.", personaggio->code);
        return NULL;
    }
    printf("Inserisci il nome dell'oggetto che vuoi inserire nell'equipaggiamento: ");
    scanf("%s", objname); getchar();
    object = searchObj(inv, objname);
    if(object!=NULL){
        personaggio->equip->vettEq[personaggio->equip->using] = object;
        personaggio->equip->using+=1;

        printf("%s aggiunto correttamente all'equipaggiamento del personaggio %s.\n", object->name, personaggio->code);
    }
    return personaggio;
}


// ! NON FUNZIONA REMOVE
PG *removeObj(PG *personaggio) {
    char objname[50];
    printf("RIMOZIONE DI UN ELEMENTO DALL'EQUIPAGGIAMENTO\n");
    if (personaggio->equip->using == 0) {
        printf("L'equipaggiamento non contiene alcun oggetto.\n");
        return personaggio;
    }
    printf("Inserisci il nome dell'oggetto che vuoi rimuovere dall'equipaggiamento: ");
    scanf("%s", objname); getchar();
    int found = 0;  // Aggiunto per tracciare se l'oggetto è stato trovato
    for (int i = 0; i < personaggio->equip->using; i++) {
        if (strncmp(strtolower(personaggio->equip->vettEq[i]->name), strtolower(objname), strlen(objname)) == 0) {
            // Rimuovi l'oggetto solo se è stato trovato
            found = 1;
            personaggio->equip->using--;

            // Sposta l'ultimo oggetto nell'equipaggiamento nella posizione dell'oggetto rimosso
            personaggio->equip->vettEq[i] = personaggio->equip->vettEq[personaggio->equip->using];
            personaggio->equip->vettEq[personaggio->equip->using] = NULL;

            printf("%s rimosso con successo.\n", objname);
            break;  // Esci dal ciclo una volta che l'oggetto è stato rimosso
        }
    }

    if (!found) {
        printf("Oggetto non trovato nell'equipaggiamento.\n");
    }

    return personaggio;
}


void printPG(PG personaggio){
    printf("---- Codice: %s\nNome: %s\nClasse: %s\nStatistiche:\n",
    personaggio.code, personaggio.name, personaggio.class);
    if(personaggio.equip->using!=0){
        // Statistiche aggiornate
        for(int i=0; i<personaggio.equip->using; i++){
            personaggio.stats.hp += personaggio.equip->vettEq[i]->stats.hp;
            if(personaggio.stats.hp<=0)
                personaggio.stats.hp=0;
            personaggio.stats.mp += personaggio.equip->vettEq[i]->stats.mp;
            if(personaggio.stats.mp<=0)
                personaggio.stats.mp=0;
            personaggio.stats.atk += personaggio.equip->vettEq[i]->stats.atk;
            if(personaggio.stats.atk<=0)
                personaggio.stats.atk=0;
            personaggio.stats.def += personaggio.equip->vettEq[i]->stats.def;
            if(personaggio.stats.def<=0)
                personaggio.stats.def=0;
            personaggio.stats.mag += personaggio.equip->vettEq[i]->stats.mag;
            if(personaggio.stats.mag<=0)
                personaggio.stats.mag=0;
            personaggio.stats.spr += personaggio.equip->vettEq[i]->stats.spr;
            if(personaggio.stats.spr<=0)
                personaggio.stats.spr=0;
        }
    }
    printStats(personaggio.stats);

    printf("Equipment:\n");
    if(personaggio.equip->using!=0){
        for(int i=0; i<personaggio.equip->using; i++){
            printf("|- %s\n", personaggio.equip->vettEq[i]->name);
        }
        printf("!!!!!!!!!! OK");
    }
    printf("----------------\n");
}

void printList(link h){
    link w = h;
    printf("Contenuto della lista:\n");
    while(w!=NULL){
        printPG(w->val);
        w = w->next;
    }
}

tabPG *insPG(tabPG *tabPers){
    PG personaggio;
    personaggio.equip = malloc(sizeof(eq));
    personaggio.equip->using = 0; personaggio.equip->vettEq = NULL;
    printf("Inserimento di un personaggio\nInserici il codice di 6 cifre del tipo PGXXXX da associare al personaggio: ");
    scanf("%s", personaggio.code); getchar();
    printf("Inserisci il nome da associare al personaggio: "); 
    scanf("%s", personaggio.name); getchar();
    printf("Inserisci la classe da associare al personaggio: "); 
    scanf("%s", personaggio.class); getchar();
    printf("Inserisci le statistiche da associare al personaggio\n");
    //     int hp, mp, atk, def, mag, spr;
    printf("HP: "); scanf("%d", &(personaggio.stats.hp)); getchar();
    printf("MP: "); scanf("%d", &(personaggio.stats.mp)); getchar();
    printf("ATK: "); scanf("%d", &(personaggio.stats.atk)); getchar();
    printf("DEF: "); scanf("%d", &(personaggio.stats.def)); getchar();
    printf("MAG: "); scanf("%d", &(personaggio.stats.mag)); getchar();
    printf("SPR: "); scanf("%d", &(personaggio.stats.spr)); getchar();
    listInsCoda(&(tabPers->headPG), &(tabPers->tailPG), personaggio);
    printf("Inserimento del personaggio %s completato con successo.\n", personaggio.code);
    printPG(personaggio);
    return tabPers;
}

tabPG *delCodice(tabPG *tabPers){
    link x=tabPers->headPG, p;
    char code[7];
    printf("Inserisci il codice di 6 caratteri dell'elemento da eliminare:\n");
    scanf("%s", code); getchar();
    if(tabPers->headPG==NULL){
        printf("La lista e' vuota.\n");
        return tabPers;
    }
    for(x, p=NULL; x!=NULL && strcmp(x->val.code, code)!=0; p=x, x=x->next);
    if(x==NULL || strcmp(x->val.code, code)!=0){ // arriva alla fine senza trovare l'elemento
        printf("Impossibile trovare l'elemento nell'inventario.\n");
        return tabPers;
    }
    if(strcmp(x->val.code, code)==0){
        if(x==tabPers->headPG){ // se l'elemento trovato e' il primo
            tabPers->headPG = tabPers->headPG->next; // la lista inizia dal secondo elmeento
        } 
        else{
            p->next = x->next;
            free(x);
        }
        printf("Elemento eliminato con successo.\n");
    }
    return tabPers;
}

tabPG *loadPGs(char *filename){
    int i;
    FILE *fp_read = fopen(filename, "r");
    PG personaggio;

    tabPG *tabPers=malloc(sizeof(tabPG));
    tabPers->nPG = 0;
    tabPers->headPG = NULL; tabPers->tailPG = NULL;

    while(!feof(fp_read)){
        fscanf(fp_read, "%s %s %s %d %d %d %d %d %d", 
        personaggio.code, personaggio.name, personaggio.class, 
        &(personaggio.stats.hp), &(personaggio.stats.mp),&(personaggio.stats.atk),
        &(personaggio.stats.def), &(personaggio.stats.mag), &(personaggio.stats.spr));
        personaggio.equip = malloc(sizeof(eq));
        personaggio.equip->using = 0;
        // Devo inserire in coda il nodo che contiene la struct di tipo PG! 
        listInsCoda(&(tabPers->headPG), &(tabPers->tailPG), personaggio);
    }
    printf("Lista caricata con successo da '%s'\n", filename);
    //printList(tabPers->headPG);
    fclose(fp_read);
    return tabPers;
}
