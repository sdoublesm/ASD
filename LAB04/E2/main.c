#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXC 25

// L'anagrafica va memorizzata in una lista ordinata per data 
// di nascita (le persone più giovani appaiono prima nella lista)

// ogni nodo della lista è una struct con dati racchiusi in un campo val di tipo Item
// e uno o due riferimenti (“link”) che puntano al nodo successivo e/o precedente
typedef struct {
    char codice[MAXC];
    char nome[MAXC];
    char cognome[MAXC];
    int datanascita;
    char via[MAXC];
    char citta[MAXC];
    int cap;
} Item;

typedef int Key;
typedef struct node *link;
// link è un alias per il puntatore a nodo
struct node{
    Item val; 
    link next; 
};

typedef enum {
    c_print, c_insTastiera, c_insFile, c_searchByCode, c_delCodice, c_delDate, c_printFile, c_exit
} comando_e;

// ---------------------------------------------------------------------------
// Funzioni gestione lista

// creazione di un nuovo nodo
// riceve come parametri cio che si vuole inserire e restituisce il puntatore al nodo
link newNode(Item val, link next){
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
link listInsHead(link h, Item val){
    h = newNode(val, h);
    return h;
}

// INSERZIONE IN CODA (algoritmo meno complesso)
void listInsCoda(link *hp, link *tp, Item val){
    if(*hp = NULL)
        *hp = *tp = newNode(val, NULL);
    else
        (*tp)->next = newNode(val, NULL);
        *tp = (*tp)->next;
}

// INSERZIONE IN LISTA ORDINATA O(n)
// richiede un altro puntatore per identificare il nodo precedessore
// lista ordinata in maniera decrescente (i piu giovani vengono prima) 
link SortListIns(link h, Item val){
    link x, p; // p e' il puntatore al predecessore
    Key k = val.datanascita;

    if(h==NULL || (h->val).datanascita <=k)
        return newNode(val, h); // inserimento in testa
    // il for serve solo a localizzare il NULL nel caso in cui si 
    // debba inserire in fondo o il secondo piu grande (tra p  e x)
    for(x=h->next, p=h; x!=NULL && k<(h->val).datanascita; p=x, x = x->next);
    p->next = newNode(val, x);
    return h;
}

void printList(link h){
    link w = h;
    printf("Contenuto della lista:\n");
    while(w!=NULL){
        printf("----- [%s] %s %s\nData di nascita: %d\nIndirizzo: %s\nCitta: %s, CAP: %d\n", 
        w->val.codice, w->val.nome, w->val.cognome, w->val.datanascita, w->val.via, w->val.citta, w->val.cap);
        w = w->next;
    }
    printf("--------------------------\n");
}

// [!] si assume che l'utente inserisca correttamente i dati
link insTastiera(link h){
    Item new;
    printf("Inserzione di un nuovo elemento da tastiera\nInserisci codice: "); scanf("%s", new.codice); getchar();
    printf("Inserisci nome: "); scanf("%s", new.nome); getchar();
    printf("Inserisci cognome: "); scanf("%s", new.cognome); getchar();
    printf("Inserisci data di nascita nel formato yyyymmdd: "); scanf("%d", &(new.datanascita)); getchar();
    printf("Inserisci indirizzo (senza spazi): "); scanf("%s", new.via); getchar();
    printf("Inserisci citta': "); scanf("%s", new.citta); getchar();
    printf("Inserisci CAP: "); scanf("%d", &(new.cap)); getchar();
    h = SortListIns(h, new);
    printf("Elemento inserito correttamente in lista.\n");
    return h;
}

link insFile(link h, char *filename){
    FILE *fp_read = fopen(filename, "r");
    int d, m, y;
    Item persona;
    if(fp_read==NULL){
        printf("Errore durante l'apertura del file.");
        return h;
    }
    while(!feof(fp_read)){
        fscanf(fp_read, "%s %s %s %d/%d/%d %s %s %d\n", 
        persona.codice, persona.nome, persona.cognome, &d, &m, &y, persona.via, persona.citta, &(persona.cap));
        persona.datanascita = y*10000+m*100+d;
        h = SortListIns(h, persona);
    }
    fclose(fp_read);
    return h;   
}

void printListOnFile(link h){
    FILE *fp_write = fopen("list.txt", "w");
    link w = h;
    while(w!=NULL){
        fprintf(fp_write, "----- [%s] %s %s\nData di nascita: %d\nIndirizzo: %s\nCitta: %s, CAP: %d\n", 
        w->val.codice, w->val.nome, w->val.cognome, w->val.datanascita, w->val.via, w->val.citta, w->val.cap);
        w = w->next;
    }
    fprintf(fp_write, "--------------------------\n");
    fclose(fp_write);
}

// Il codice e' univoco, ci sara' al massimo solo un risultato
void searchByCode(link h, char code[MAXC]){
    link x;
    printf("Risultato della ricerca:\n");
    for(x=h; x!=NULL && strcmp(x->val.codice, code)!=0; x=x->next);
    if(x==NULL){
        printf("Nessun risultato.\n");
        return;        
    }
    printf("----- [%s] %s %s\nData di nascita: %d\nIndirizzo: %s\nCitta: %s, CAP: %d\n", 
    x->val.codice, x->val.nome, x->val.cognome, x->val.datanascita, x->val.via, x->val.citta, x->val.cap);   
}

link delCodice(link h, char code[MAXC]){
    link x=h, p;
    if(h==NULL){
        printf("La lista e' vuota.\n");
        return h;
    }
    for(x=h, p=NULL; x!=NULL && strcmp(x->val.codice, code)!=0; p=x, x=x->next);
    if(x==NULL || strcmp(x->val.codice, code)!=0){ // arriva alla fine senza trovare l'elemento
        printf("Impossibile trovare l'elemento.\n");
        return h;
    }
    if(strcmp(x->val.codice, code)==0){
        if(x==h){ // se l'elemento trovato e' il primo
            h = h->next; // la lista inizia dal secondo elmeento
        } 
        else{
            p->next = x->next;
            free(x);
        }
        printf("Elemento eliminato con successo.\n");
    }
    return h;
}

link delDate(link h, int d1, int d2){
    link x=h, p;
    if(h==NULL){
        printf("La lista e' vuota.\n");
        return NULL;
    }
    for(x=h, p=NULL; x!=NULL && (x->val.datanascita<d1 || x->val.datanascita>d2); p=x, x=x->next);
    if(x==NULL){ // arriva alla fine senza trovare l'elemento
        // printf("[delDate] Nessun elemento da eliminare.\n");
        return NULL;
    }    
    return x;
}

// ---------------------------------------------------------------------------
// Funzioni gestione menu

char * strtolower(char s[]){
    for(int i=0;s[i]!='\0';i++){
        s[i]=tolower(s[i]);
    }
    return s;
}

comando_e leggiComando(){
    comando_e cmd;
    char parola[MAXC], cmdlist[c_exit+1][30]={"print", "insTastiera", "insFile", "searchByCode", "delCodice", "delDate", "printFile", "exit"};
    printf("> Inserisci il nome di un comando: ");
    scanf("%s", parola); 
    getchar(); // scanf lascia \n nel buffer!!!
    for(cmd=c_print; cmd<=c_exit; cmd++){
        if(strcmp(strtolower(parola), strtolower(cmdlist[cmd]))==0)
            return cmd;
    }
    return -1;
}

void menu(link h){
    comando_e cmd;
    link r;
    int continua = 1, d1, d2;
    char code[MAXC], filename[MAXC];

    while(continua==1){  
        printf("\n----------------------\n");
        printf("MENU OPZIONI ---------\n");
        printf("0. print\n1. insTastiera\n2. insFile\n3. searchByCode\n4. delCodice\n5. delDate\n6. printFile\n7. exit\n");
        printf("----------------------\n");
        cmd = leggiComando();
        switch(cmd){
            case c_print:
                printList(h);
                break; 
            case c_insTastiera:
                h = insTastiera(h);
                break;
            case c_insFile:
                printf("Inserisci il nome del file da cui caricare i dati: ");
                scanf("%s", filename); getchar();
                h = insFile(h, filename);
                printf("Lista caricata correttamente dal file '%s'", filename);
                break;
            case c_searchByCode:
                printf("Inserisci il codice da cercare: "); 
                scanf("%s", code); getchar();
                searchByCode(h, code);
                break;
            case c_delCodice:
                printf("Inserisci il codice dell'elemento da eliminare: "); 
                scanf("%s", code); getchar();
                h = delCodice(h, code);
                break;
            case c_delDate:
                printf("Eliminazione di elementi con data di nascita compresa tra d1 e d2\nInserisci d1 nel formato yyyymmdd: ");
                scanf("%d", &d1); getchar();
                printf("Inserisci d2 nel formato yyyymmdd: ");
                scanf("%d", &d2); getchar();
                r = delDate(h, d1, d2);
                if(r==NULL)
                    printf("Nessun risultato.\n");
                while(r!=NULL){
                    printf("Eliminazione dell'elemento con codice %s...\n", r->val.codice);
                    h = delCodice(h, r->val.codice);
                    r = delDate(h, d1, d2);
                }
                break;
            case c_printFile:
                printListOnFile(h);
                printf("Lista correttamente scritta sul file 'list.txt'.\n");
                break;            
            case c_exit:
                printf("Chiusura del programma...");
                continua = 0;
                break;
            default:
                printf("[!] Comando non riconosciuto. Riprova.\n");
        }
    }
}

// ---------------------------------------------------------------------------

int main(void){
    link head = NULL;
    head = insFile(head, "anag1.txt");
    printf("Lista caricata correttamente.");
    menu(head);    
    return 0;
}