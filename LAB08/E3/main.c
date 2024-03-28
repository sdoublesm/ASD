#include <stdio.h>
#include <stdlib.h>
#include "titles.h"

/*
sistema che tenga conto di tutte le borse, per la memorizzzione e 
gestione dei titoli azionari. 
file con elenco di transizioni raggruppate per i titoli e le relative 
transazioni

struttura dati a 2 livelli: 
1) collezione di titoli e per ogni titolo 2) una collezione delle 
sue quot giornaliere.
*/

int main(void) {
    int i, c=1, f=0; // f: flag file caricato
    char name[MAXC];
    FILE *fin; LISTtitle l=LISTinit();

    while(c){
        printf("\n"
        "COMANDI -----------------------------------\n"
        "1 | Carica titoli da file\n"
        "2 | Ricerca di un titolo azionario\n"
        "3 | Ricerca quotazione dato un titolo in una certa data\n"
        "4 | Ricerca quotazione minima e massima dato un titolo (in un range di date)\n"
        "5 | Ricerca della quotazione minima e massima dato un titolo (globale)\n"
        "6 | Bilanciamento del BST dato un titolo\n"
        "7 | Esci\n");
        printf("Inserici codice comando (intero): ");
        
        if(scanf("%d",&i)<=0) {
            printf("Devi inserire un intero!\n");
            return(-1);
        }
        else {
            switch(i) {
                case 1:
                    f=1;
                    printf("Inserisci filename: ");
                    scanf("%s", name);
                    fin = fopen(name, "r");
                    if (fin == NULL) 
                        return(-1);
                    l=readfile(fin,l);
                    fclose(fin);
                    break;
                case 2:
                    if(f==1) searchTITLE(l);
                    else 
                        printf("Devi prima caricare un file!\n");
                    break;
                case 3:
                    if(f==1) searchTITLEQuotationFromDate(l);
                    else 
                        printf("Devi prima caricare un file!\n");
                    break;
                case 4:
                    if(f==1) searchQuotfromRange(l);
                    else 
                        printf("Devi prima caricare un file!\n");
                    break;
                case 5:
                    if(f==1) searchTITLEQuotationMINMAXFromAllPeriod(l);
                    else 
                        printf("Devi prima caricare un file!\n");
                    break;
                case 6:
                    if(f==1) balanceW(l);
                    else 
                        printf("Devi prima caricare un file!\n");
                    break;
                case 7:     
                    c = 0;
                    break;
                default:    
                    printf("Comando non riconosciuto\n");
            }
        }
    }
    LISTfree(l);
    return 0;
}