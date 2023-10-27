#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTRATTE 1000
#define MAXLEN 30

// Esercizio n. 3: Azienda di trasporti - ordinamento

typedef struct {
    char codice[MAXLEN], partenza[30], destinazione[30], h_partenza[30], h_arrivo[30];
    int data, ritardo;
} tratta;

typedef enum {
    c_stampa, c_sortData, c_sortCodice, c_sortPartenza, c_sortArrivo, c_ricercaPartenza, c_fine
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
void stampa(tratta tratte[MAXTRATTE], int dim){
    char c; int i; tratta t;
    char p[1000];
    printf("Inserisci il carattere 'v' per stampare le informazioni a video o 'f' per stamparle su file: ");  
    // getchar(); 
    c = getchar();
    if(c=='v'){
        printf("\nElenco tratte:\n");
        for(i=0; i<dim; i++){
            printf(getprint(tratte[i], p));
        }
    }
    else if(c=='f'){
        FILE *fpwrite=fopen("output.txt", "w");
        for(i=0; i<dim; i++){
            t = tratte[i];
            fprintf(fpwrite, getprint(tratte[i], p));
        }
        fclose(fpwrite);
        printf("Contenuto stampato nel file 'output.txt'.\n");
    }
    else{
        printf("[!] Scelta non valida.");
    }
}
    
// 2. ordinamento per data
void sortData(tratta tratte[MAXTRATTE], int dim){
    tratta tmp; int i, j;

    // insertion sort: algoritmo stabile
    
    // sort ora partenza
    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && htoint(tmp.h_partenza)<htoint(tratte[j].h_partenza)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }

    // sort data
    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && tmp.data<(tratte[j].data)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }

    printf("Sorting per data e ora effettuato.\n");
    stampa(tratte, dim);
}

// 3. ordinamento per codice
void sortCodice(tratta tratte[MAXTRATTE], int dim){
    tratta tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && codetoint(tmp.codice)<codetoint(tratte[j].codice)){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    stampa(tratte, dim);
}

// 4. ordinamento per partenza
void sortPartenza(tratta tratte[MAXTRATTE], int dim){
    tratta tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp.partenza, tratte[j].partenza)<0){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    stampa(tratte, dim);
}

// 5. ordinamento per destinazione
void sortArrivo(tratta tratte[MAXTRATTE], int dim){
    tratta tmp; int i, j;

    for(i = 1; i < dim; i++){
        tmp = tratte[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp.destinazione, tratte[j].destinazione)<0){
            tratte[j+1] = tratte[j];
            j--;
        }
        tratte[j+1] = tmp;
    }
    stampa(tratte, dim);
}

// 6. ricerca fermata di partenza
void ricercaPartenza(){
}

// -------------------------------------------------------------------------

comando_e leggiComando(){
    comando_e cmd;
    char parola[MAXLEN], cmdlist[c_fine+1][30]={"stampa", "sortData", "sortCodice", "sortPartenza", "sortArrivo", "searchPartenza", "fine"};
    printf("> Inserisci il nome di un comando: ");
    scanf("%s", parola);
    getchar(); // scanf lascia \n nel buffer!!!
    for(cmd=c_stampa; cmd<=c_fine; cmd++){
        if(strcmp(parola, cmdlist[cmd])==0){
            return cmd;
        }
    }
}

void menu(tratta tratte[MAXTRATTE], int dim){
    comando_e cmd;
    int continua = 1;
    
    while(continua==1){
        printf("\n----------------------\n");
        printf("MENU OPZIONI ---------\n");
        printf("1. stampa\n2. sortData\n3. sortCodice\n4. sortPartenza\n5. sortArrivo\n6. ricercaPartenza\n7. fine\n");
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
            case c_fine:
                printf("Chiusura del programma...");
                continua = 0;
                break;
            default:
                printf("[!] Comando non riconosciuto. Riprova.\n");
        }
    }
}

int main(void){
    int n, h_p, h_a, mi_p, mi_a, s_p, s_a, d, y, mo;
    FILE *fp_read=fopen("log.txt", "r");
    tratta pointers[MAXTRATTE];

    if(fp_read==NULL){
        printf("[!] Errore nell'apertura del file\n");
        return -1;
    }

    fscanf(fp_read, "%d\n", &n);
    tratta tratte[n];
    for(int i=0; i<n; i++){
        fscanf(fp_read, "%s %s %s %d/%d/%d %s %s %d\n", 
        tratte[i].codice, tratte[i].partenza, tratte[i].destinazione, 
        &y, &mo, &d, tratte[i].h_partenza, tratte[i].h_arrivo, &(tratte[i].ritardo));
        // data e' un intero con formato yyyymmdd
        tratte[i].data = y*10000+mo*100+d;
    }


    fclose(fp_read);

    menu(tratte, n);

    return 0;
}