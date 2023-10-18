#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardotot, r_fine
} comando_e;

typedef struct {
    char codice[30], partenza[30], destinazione[30], h_partenza[30], h_arrivo[30];
    int data, ritardo;
} tratta;

/*
 * Dopo aver letto il file e acquisito il contenuto in una opportuna struttura dati, 
 * si scriva un programma in C che fornisca un menu all’utente per 
 * scegliere tra una delle seguenti operazioni:
 * [x] elencare tutte le corse partite in un certo intervallo di date
 * [x] elencare tutti le corse partite da una certa fermata (partenza)
 * [x] elencare tutti le corse aventi una specifica destinazione (capolinea)
 * [x] elencare tutte le corse che hanno raggiunto la destinazione in ritardo, 
 * in un certo intervallo di date
 * 5. elencare il ritardo complessivo accumulato dalle corse 
 * identificate da un certo codice di tratta
 * [x] terminare il programma
*/

char * strtolower(char s[]){
    for(int i=0;s[i]!='\0';i++){
        s[i]=tolower(s[i]);
    }
    return s;
}

// stampa dettagli tratta
void printTratta(tratta t){
    printf("------------------------------\n");
    printf("Codice: %s\n", t.codice);
    printf("Partenza: %s\n", t.partenza);
    printf("Destinazione: %s\n", t.destinazione);
    printf("Data: %d\n", t.data);
    printf("Ora partenza: %s\n", t.h_partenza);
    printf("Ora arrivo: %s\n", t.h_arrivo);
    printf("Ritardo: %d minuti\n", t.ritardo);
    printf("------------------------------\n\n");    
}

// 1. date
void date(tratta tratte[], int dim){
    int d1, d2;
    printf("Inserisci due date (yyyymmdd) in ordine cronologico separate da uno spazio: ");
    scanf("%d %d", &d1, &d2);
    printf("partenze comprese tra %d e %d:\n", d1, d2);
    for(int i=0; i<dim; i++){
        if(tratte[i].data<=d2 && tratte[i].data>=d1){
            printTratta(tratte[i]);
        }
    }
}

// 2. partenza
void partenza(tratta tratte[], int dim){
    char fermata[30];
    printf("Inserisci una fermata di partenza: ");
    scanf("%s", fermata);
    for(int i=0; i<dim; i++){
        if(strcmp(strtolower(tratte[i].partenza), strtolower(fermata))==0){
            printTratta(tratte[i]);
        }
    }
}

// 3. capolinea
void capolinea(tratta tratte[], int dim){
    char fermata[30];
    printf("Inserisci una fermata capolinea: ");
    scanf("%s", fermata);
    for(int i=0; i<dim; i++){
        if(strcmp(strtolower(tratte[i].destinazione), strtolower(fermata))==0){
            printTratta(tratte[i]);
        }
    }
}

// 4. ritardo
void ritardo(tratta tratte[], int dim){
    int d1, d2;
    printf("Inserisci due date (yyyymmdd) in ordine cronologico separate da uno spazio e ti restituiro le tratte che sono in ritardo: ");
    scanf("%d %d", &d1, &d2);
    for(int i=0; i<dim; i++){
        if(tratte[i].data<=d2 && tratte[i].data>=d1 && tratte[i].ritardo!=0){
            printTratta(tratte[i]);
        }
    }
}

// 5. ritardo_tot
void ritardo_tot(tratta tratte[], int dim){
    int ritardo = 0;
    char codice[7];
    printf("Inserisci un codice di tratta: ");
    scanf("%s", &codice);
    for(int i=0; i<dim; i++){
        if(strcmp(strtolower(codice), strtolower(tratte[i].codice))==0){
            ritardo += tratte[i].ritardo;
        }
    }
    printf("Tratta: %s\nRitardo totale: %d minuti\n", codice, ritardo);
}

 comando_e leggiComando(){
    comando_e cmd;
    char parola[30], cmdlist[r_fine+1][30]={"date", "partenza", "capolinea", "ritardo", "ritardotot", "fine"};
    printf("> Inserisci un comando: ");
    scanf("%s", parola);
    for(cmd=r_date; cmd<=r_fine; cmd++){
        if(strcmp(parola, cmdlist[cmd])==0){
            return cmd;
        }
    }
}

void menu(tratta tratte[], int dim){
    comando_e cmd;
    int continua=-1;
    
    while(continua){
        printf("\nMENU OPZIONI ---------\n");
        printf("1. date\n2. partenza\n3. capolinea\n4. ritardo\n5. ritardotot\n6. fine\n");
        printf("----------------------\n");
        cmd = leggiComando();
        switch(cmd){
            case r_date:
                date(tratte, dim);
                break;
            case r_partenza:
                partenza(tratte, dim);
                break;
            case r_capolinea:
                capolinea(tratte, dim);
                break;
            case r_ritardo:
                ritardo(tratte, dim);
                break;
            case r_ritardotot:
                ritardo_tot(tratte, dim);
                break;
            case r_fine:
                continua=0;
                break;
            default:
                printf("Comando non riconosciuto. Riprova.\n");
        }
    }
}

int main(void){
    int n, h_p, h_a, mi_p, mi_a, s_p, s_a, d, y, mo;
    FILE *fp_read=fopen("log.txt", "r");

    if(fp_read==NULL){
        printf("Errore nell'apertura del file\n");
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