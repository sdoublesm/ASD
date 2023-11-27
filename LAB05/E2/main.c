#include <stdio.h>
#include <stdlib.h>
#define tFILENAME "tiles.txt"
#define bFILENAME "board.txt"

// Esercizio n. 2: Tessere e scacchiere

typedef struct{
    char cT1;
    int vT1;
    char cT2;
    int vT2;
} tile;

/*
* Per ottenere i punti associati ai vari segmenti, 
* è necessario allineare lungo un'intera riga o colonna
* tubi in orizzontale o verticale dello stesso colore
* quindi SOLO RIGHE E COLONNE COMPLETE contribuiscono al punteggio
* le tessere possono essere ruotate di 90 gradi
* si assuma esistano abbastanza tessere per completare la scacchiera

* scopo del gioco: ottenere il massimo punteggio possibile
* posizionando una tessera in ogni cella della scacchiera
*/

/* su tiles.txt elenco tessere disponibili nel formato
* - numero di tessere sulla prima riga
* - T quadruple nella forma <coloreT1><valoreT1><coloreT2><valoreT2>
* che descrive la coppia di tubi presenti sulla tessera
* ASSUMERE CHE A OGNI TESSERA SIA ASSOCIATO UN IDENTIFICATIVO NUMERICO NELL'INTERVALLO 0..T-1

* su board.txt è riportata una configurazione iniziale per la scacchiera del gioco
* R e C su prima riga
* configurazione celle: indice tessera tra quelle presenti in tiles / rotazione (0 o 1)
* cella vuota rappresentata come -1/-1

// GENERARE LA SOLUZIONE A PUNTEGGIO MASSIMO POSSIBILE A PARTIRE DALLA CONFIGURAZIONE INIZIALE LETTA DA FILE
*/

tile *rotate(tile *tile){
    char ctemp, vtemp;
    // inverti cT1 e vT1 con cT2 e vT2
    if(tile->cT1!=tile->cT2 && tile->vT1!=tile->vT2){
        ctemp = tile->cT1; vtemp = tile->vT1;
        tile->cT1 = tile->cT2; tile->vT1 = tile->vT2;
        tile->cT2 = ctemp; tile->vT1 = vtemp;
    }
    return tile;
}

tile *loadTiles(char *filename){
    FILE *fp_read = fopen(filename, "r");
    int nt, i;
    tile *availableTiles;
    if(fp_read==NULL){
        printf("Errore durante l'apertura del file '%s'.", filename);
        return NULL;
    }
    printf("File tessere '%s' caricato correttamente.\n", filename);
    fscanf(fp_read, "%d\n", &nt);
    availableTiles = calloc(nt, sizeof(tile));
    printf("%d tessere disponibili:\n", nt);
    for(i=0; i<nt; i++){
        fscanf(fp_read, "%c %d %c %d\n", &(availableTiles[i].cT1), &(availableTiles[i].vT1), &(availableTiles[i].cT2), &(availableTiles[i].vT2));
        printf("%c %d %c %d\n", availableTiles[i].cT1, availableTiles[i].vT1, availableTiles[i].cT2, availableTiles[i].vT2);
    }
    fclose(fp_read);
    return availableTiles;
}

// Struttura dati: MATRICE CONTENENTE TILES (struct)
tile **loadMatrix(char *filename, tile *avTiles){
    FILE *fp_read = fopen(filename, "r");
    tile **matrix;
    int i, j, k, nr, nc, rot;

    if(fp_read==NULL){
        printf("Errore durante l'apertura del file '%s'.", filename);
        return NULL;
    }
    fscanf(fp_read, "%d %d\n", &nr, &nc);
    // allocazione dinamica matrice (no free)
    matrix = malloc(nr*sizeof(tile*));
    for(i=0; i<nr; i++){
        matrix[i] = malloc(nc*sizeof(tile));
    }
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            fscanf(fp_read, "%d/%d", &k, &rot);
            // cella vuota
            matrix[i][j] = avTiles[k];
            if(k==-1 && rot==-1){ 
                matrix[i][j].vT1 = 0;
                matrix[i][j].vT2 = 0;                 
            }
            if(rot==1)
                rotate(&(matrix[i][j]));
        }
    }
    fclose(fp_read);
    return matrix;
}

int main(void){
    tile *availableTiles = loadTiles(tFILENAME), **matrix = loadMatrix(bFILENAME, availableTiles);
    return 0;
}