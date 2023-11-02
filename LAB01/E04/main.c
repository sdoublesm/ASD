#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTRATTE 1000
#define MAXLEN 30

// Esercizio n. 3: Azienda di trasporti - multiordinamento
// gli ordinamenti vanno mantenuti
// le funzioni lavorano sul vettore di struct passate by reference

typedef struct {
    char codice[MAXLEN], partenza[30], destinazione[30], h_partenza[30], h_arrivo[30];
    int data, ritardo;
} tratta;

typedef enum {
    c_stampa, c_sortData, c_sortCodice, c_sortPartenza, c_sortArrivo, c_ricercaPartenza, c_exit
} comando_e;

// -------------------------------------------------------------------------

char * strtolower(char s[]){
    for(int i=0;s[i]!='\0';i++){
        s[i]=tolower(s[i]);
    }
    return s;
}

int htoint(char orario[10]){
    int h, m, s;
    sscanf(orario, "%d:%d:%d", &h, &m, &s);
    return (h * 3600) + (m * 60) + s;
}

int codetoint(char codice[10]){
    int c;
    sscanf(codice, "GTT%d", &c);
    return c;
}

char *getprint(tratta t, char *s){
    sprintf(s, "------------------------------\nCodice: %s\nPartenza: %s\nDestinazione: %s\nData: %d\nOra partenza: %s\nOra arrivo: %s\nRitardo: %d minuti\n", 
    t.codice, t.partenza, t.destinazione, t.data, t.h_partenza, t.h_arrivo, t.ritardo);
    return s;
}

// -------------------------------------------------------------------------

// 1. stampa a video o su file i dettagli delle tratte
void stampa(tratta **tratte, int dim){
    char c; int i; tratta t;
    char p[1000];
    printf("Inserisci il carattere 'v' per stampare le informazioni a video o 'f' per stamparle su file: ");  
    // getchar(); 
    c = getchar();
    if(c=='v'){
        printf("\nElenco tratte:\n");
        for(i=0; i<dim; i++){
            printf(getprint(*tratte[i], p));
        }
        printf("------------------------------\n");
    }
    else if(c=='f'){
        FILE *fp_write=fopen("output.txt", "w");
        for(i=0; i<dim; i++){
            fprintf(fp_write, getprint(*tratte[i], p));
        }
        fprintf(fp_write, "------------------------------\n");
        fclose(fp_write);
        printf("Contenuto stampato nel file 'output.txt'.\n");
    }
    else{
        printf("[!] Scelta non valida.");
    }
}

// 2. ordinamento per data
void sortData(tratta **tratte, int dim){
    tratta *tmp; int i, j;

    // insertion sort: algoritmo stabile
    
    // sort ora partenza
    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && htoint(tmp->h_partenza)<htoint(tratte[j]->h_partenza)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }

    // sort data
    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && tmp->data<(tratte[j]->data)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }

    printf("Sorting per data e ora effettuato.\n");
    stampa(tratte, dim);
}

// 3. ordinamento per codice
void sortCodice(tratta **tratte, int dim){
    tratta *tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && codetoint(tmp->codice)<codetoint(tratte[j]->codice)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    printf("Sorting per codice tratta effettuato.\n");
    stampa(tratte, dim);
}

// 4. ordinamento per partenza
void sortPartenza(tratta **tratte, int dim){
    tratta *tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp->partenza, tratte[j]->partenza)<0){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    printf("Sorting per stazione di partenza effettuato.\n");
    stampa(tratte, dim);
}

// 5. ordinamento per destinazione
void sortArrivo(tratta **tratte, int dim){
    tratta *tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp->destinazione, tratte[j]->destinazione)<0){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    printf("Sorting per stazione di arrivo effettuato.\n");
    stampa(tratte, dim);
}

// 6. ricerca fermata di partenza
void ricercaLineare(tratta **tratte, int dim, char tosearch[]){
    int found=0; 
    char p[1000];
    printf("\nRisultati della ricerca lineare:\n");
    for(int i=0;i<dim;i++){
        if(strncmp(strtolower(tosearch), strtolower(tratte[i]->partenza), strlen(tosearch))==0){
            found = 1;
            printf(getprint(*tratte[i], p));
        }
    }
    if (found!=0)
        printf("Nessun risultato.\n");
}

void ricercaDicotomica(tratta **tratte, int dim, char tosearch[]) {
    int start = 0, end = dim - 1, m, i, j, cmp, found = 0;
    char p[1000];
    printf("\nRisultati della ricerca dicotomica:\n");
    while(start <= end && found==0) {
        m = (start + end) / 2;
    if(strncmp(strtolower(tratte[m]->partenza), strtolower(tosearch), strlen(tosearch)) == 0) {
        found = 1;
    } else {
        if(cmp < 0)
            start = m + 1;
        else
            end = m - 1;
    }
  }
  if(found==1) {
    i = m;
    j = m -1;
    while(i < dim && strncmp(strtolower(tratte[i]->partenza), strtolower(tosearch), strlen(tosearch)) == 0) {
        printf(getprint(*tratte[i], p));
        i++;
    }
    while(j>=0 && strncmp(strtolower(tratte[j]->partenza), strtolower(tosearch), strlen(tosearch)) == 0) {
        printf(getprint(*tratte[j], p));
        j--;
    }
  } else
        printf("Nessun risultato.\n");
}

// -------------------------------------------------------------------------

comando_e leggiComando(){
    comando_e cmd;
    char parola[MAXLEN], cmdlist[c_exit+1][30]={"stampa", "sortData", "sortCodice", "sortPartenza", "sortArrivo", "ricercaPartenza", "exit"};
    printf("> Inserisci il nome di un comando: ");
    scanf("%s", parola); 
    getchar(); // scanf lascia \n nel buffer!!!
    for(cmd=c_stampa; cmd<=c_exit; cmd++){
        if(strcmp(strtolower(parola), strtolower(cmdlist[cmd]))==0)
            return cmd;
    }
    return -1;
}

void menu(tratta **tratte, int dim){
    comando_e cmd;
    int continua = 1;
    char strtosearch[MAXLEN];

    while(continua==1){  
        printf("\n----------------------\n");
        printf("MENU OPZIONI ---------\n");
        printf("1. stampa\n2. sortData\n3. sortCodice\n4. sortPartenza\n5. sortArrivo\n6. ricercaPartenza\n7. exit\n");
        printf("----------------------\n");
        cmd = leggiComando();
        switch(cmd){
            case c_stampa:
                stampa(tratte, dim);
                break;
            case c_sortData:
                sortData(tratte, dim);
                break;
            case c_sortCodice:
                sortCodice(tratte, dim);
                break;
            case c_sortPartenza:
                sortPartenza(tratte, dim);
                break;
            case c_sortArrivo:
                sortArrivo(tratte, dim);
                break;
            case c_exit:
                printf("Chiusura del programma...");
                continua = 0;
                break;
            case c_ricercaPartenza:
                printf("Inserisci stringa da cercare attraverso ricerca lineare: ");
                scanf("%s",strtosearch); getchar();
                ricercaDicotomica(tratte, dim, strtosearch);
                break;
            default:
                printf("[!] Comando non riconosciuto. Riprova.\n");
        }
    }
}

int main(void){
    int n, i, y, mo, d;
    FILE *fp_read=fopen("log.txt", "r");

    if(fp_read==NULL){
        printf("[!] Errore nell'apertura del file\n");
        return -1;
    }

    fscanf(fp_read, "%d\n", &n);
    tratta tratte[n];
    tratta *ptotratte[n];

    for(i=0; i<n; i++){
        fscanf(fp_read, "%s %s %s %d/%d/%d %s %s %d\n", 
        tratte[i].codice, tratte[i].partenza, tratte[i].destinazione, 
        &y, &mo, &d, tratte[i].h_partenza, tratte[i].h_arrivo, &(tratte[i].ritardo));
        // data e' un intero con formato yyyymmdd
        tratte[i].data = y*10000+mo*100+d;
    }
    fclose(fp_read);

    for(i=0; i<n; i++){
        ptotratte[i] = &tratte[i];
    }

    menu(ptotratte, n);

    return 0;
}