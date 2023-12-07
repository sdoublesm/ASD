#include "pg.h" // a sua volta include inventario.h

/*
Si scriva un programma in C che permetta di:
* [x] caricare in una lista l’elenco di personaggi
* [x] caricare in un vettore di strutture, allocato dinamicamente, l’elenco di oggetti 
* [x] aggiungere un nuovo personaggio 
* [x] eliminare un personaggio 
* [x] aggiungere/rimuovere un oggetto dall’equipaggiamento di un personaggio 
* [x] calcolare le statistiche di un personaggio tenendo in considerazione i suoi 
* parametri base e l’equipaggiamento corrente, applicando quindi i bonus e 
* i malus dell'equipaggiamento stesso. Se una certa statistica risultasse 
* inferiore a 0 in seguito all'applicazione dei malus, in fase di visualizzazione 
* si stampi 0, per convenzione, anziché il valore negativo 
* assunto dalla statistica stessa. 
*/

typedef enum {
    c_loadPGs, c_loadObjects, c_addPG, c_delPG, c_addObj, c_delObj, c_printDetails, c_exit
} comando_e;

void menu(tabObj *tabObjects, tabPG *tabpers);


comando_e leggiComando(){
    comando_e cmd;
    char parola[50], cmdlist[c_exit+1][30]={"caricaPersonaggi", "caricaOggetti", "aggiungiPersonaggio", 
    "rimuoviPersonaggio", "aggiungiOggetto", "rimuoviOggetto", "stampaDettagli", "esci"};
    printf("> Inserisci il nome di un comando: ");
    scanf("%s", parola); getchar();
    for(cmd=c_loadPGs; cmd<=c_exit; cmd++){
        if(strcmp(strtolower(parola), strtolower(cmdlist[cmd]))==0)
            return cmd;
    }
    return -1;
}

void menu(tabObj *tabObjects, tabPG *tabPers){
    comando_e cmd;
    link pgnode;
    int continua = 1;
    char strtosearch[50], filename[50], pname[50];

    while(continua==1){  
        printf("\n----------------------\n");
        printf("MENU OPZIONI ---------\n");
        printf("1. caricaPersonaggi\n2. caricaOggetti\n3. aggiungiPersonaggio\n4. rimuoviPersonaggio\n5. aggiungiOggetto\n5. rimuoviOggetto\n6. stampaDettagli\n7. esci\n");
        printf("----------------------\n");
        cmd = leggiComando();
        switch(cmd){
            case c_loadPGs:
                printf("Inserisci il nome del file da cui caricare la lista dei personaggi: "); 
                scanf("%s", filename); getchar();
                tabPers = loadPGs(filename);
                if(tabPers!=NULL)
                    printList(tabPers->headPG);
                else
                    printf("Riprova");
                break;
            case c_loadObjects:
                printf("Inserisci il nome del file da cui caricare l'inventario: "); 
                scanf("%s", filename); getchar();
                tabObjects = loadObjects(filename);
                break;
            case c_addPG:
                insPG(tabPers);
                break;
            case c_delPG:
                delCodice(tabPers);
                break;
            case c_addObj:
                addObj(tabPers, tabObjects);
                break;
            case c_delObj:
                removeObj(tabPers);
                break;
            case c_printDetails:
                pgnode = searchByCode(tabPers->headPG);
                if(pgnode==NULL)
                    printf("Personaggio non trovato. Impossibile mostrarne i dettagli.");
                else{
                    printf("\nDettagli personaggio:\n");
                    printPG(pgnode->val);
                }
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

int main(void){
    tabObj *tabObjects = malloc(sizeof(tabObj));
    tabPG *tabPers = malloc(sizeof(tabPG));

    tabObjects = loadObjects("inventario.txt");
    tabPers = loadPGs("pg.txt");
    menu(tabObjects, tabPers);

    return 0;
}