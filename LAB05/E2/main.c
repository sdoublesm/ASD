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
    int mark;
} tile;

typedef struct {
    tile tile;
    int rot;
    int used;    
} box;

/*
* Per ottenere i punti associati ai vari segmenti, 
* è necessario allineare lungo un'intera riga o colonna
* tubi in orizzontale o verticale dello stesso colore
* quindi SOLO RIGHE E COLONNE COMPLETE contribuiscono al punteggio
* le tessere possono essere ruotate di 90 gradi
* si assuma esistano abbastanza tessere per completare la scacchiera

* scopo del gioco: ottenere il massimo punteggio possibile
* posizionando una tessera in ogni cella della scacchiera
! N.B. logica molto simile al sudoku
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

? GENERARE LA SOLUZIONE A PUNTEGGIO MASSIMO POSSIBILE A PARTIRE DALLA CONFIGURAZIONE INIZIALE LETTA DA FILE
*/

box *rotate(box *b){
    char ctemp, vtemp;
    // inverti cT1 e vT1 con cT2 e vT2
    if(b->tile.cT1!=b->tile.cT2 && b->tile.vT1!=b->tile.vT2){
        ctemp = b->tile.cT1; vtemp = b->tile.vT1;
        b->tile.cT1 = b->tile.cT2; b->tile.vT1 = b->tile.vT2;
        b->tile.cT2 = ctemp; b->tile.vT1 = vtemp;
    }
    return b;
}

void printBoard(box **board, int R, int C){
    printf("\nSchema scacchiera:\n");
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(board[i][j].used==1){
                if(board[i][j].rot==0)
                    printf("(%c%d, %c%d) ",(board[i][j].tile.cT1),(board[i][j].tile.vT1),(board[i][j].tile.cT2),(board[i][j].tile.vT2));
                else if(board[i][j].rot==1)
                    printf("(%c%d, %c%d) ",(board[i][j].tile.cT2),(board[i][j].tile.vT2),(board[i][j].tile.cT1),(board[i][j].tile.vT1));
            } else
                printf("- ");
        }
        printf("\n");
    }
    printf("----------------------------");
}

int checkscore(box **board, int R, int C, tile *tiles, int maxscore, box ****sol){
    int i,j, osum, vsum, osumtot=0, vsumtot=0, flag;
    char col;

    for(i=0;i<R;i++){
        if(board[i][0].rot==0) 
            col = board[i][0].tile.cT1;
        else 
            col = board[i][0].tile.cT2;
        flag=1; osum=0;
        for(j=0;j<R;j++){
            if(board[i][j].rot==0 && col==board[i][j].tile.cT1 && flag==1){
                osum+=board[i][j].tile.vT1;
            } else if(board[i][j].rot==1 && col==board[i][j].tile.cT2 && flag==1){
                osum+=board[i][j].tile.vT2;
            } else{
                osum=0;
                flag=0;
            }
        }
        osumtot+=osum;
    }

    for(j=0;j<C;j++){
        if(board[0][j].rot==0) col=board[0][j].tile.cT2;
        else col=board[0][j].tile.cT1;
        flag=1;
        vsum=0;
        for(i=0;i<R;i++){
            if(board[i][j].rot==0 && col==board[i][j].tile.cT2 && flag==1)
                vsum=vsum+board[i][j].tile.vT2;
            else if(board[i][j].rot==1 && col==board[i][j].tile.cT1 && flag==1)
                vsum+=board[i][j].tile.vT1;
            else{
                vsum=0;
                flag=0;
            }
        }
        vsumtot+=vsum;
    }

    if((osumtot+vsumtot)>maxscore){
        maxscore=vsumtot+osumtot;
        for(i=0;i<R;i++){
            for(j=0;j<C;j++){
                (**sol)[i][j] = board[i][j];
            }
        }
        return maxscore;
    }
    return maxscore;
}

int disp_rip(int pos, box **board, tile *tiles, int R, int C, int maxpunti, box ***sol){
    int i,j,k;
    if(pos>=(R*C)){
        maxpunti = checkscore(board,R,C,tiles,maxpunti,&sol);
        return maxpunti;
    }
    i=pos/R; j=pos%R;
    if(board[i][j].used!=0){
        maxpunti=disp_rip(pos+1,board,tiles,R,C,maxpunti,sol);
        return maxpunti;
    }
    for(k=0;k<(R*C);k++){
        if(tiles[k].mark==0){
            board[i][j].used=1;
            board[i][j].tile=tiles[k];
            tiles[k].mark=1;

            board[i][j].rot=0;
            maxpunti=disp_rip(pos+1,board,tiles,R,C,maxpunti,sol);
            board[i][j].rot=1;
            maxpunti=disp_rip(pos+1,board,tiles,R,C,maxpunti,sol);

            board[i][j].used=0;
            tiles[k].mark=0;
        }
    }
    return maxpunti;
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
        printf("%c%d %c%d\n", availableTiles[i].cT1, availableTiles[i].vT1, availableTiles[i].cT2, availableTiles[i].vT2);
    }
    fclose(fp_read);
    return availableTiles;
}

// Struttura dati: MATRICE CONTENENTE TILES (struct)
box **loadMatrix(char *filename, tile *avTiles, int *nr, int *nc){
    FILE *fp_read = fopen(filename, "r");
    box **matrix;
    int i, j, k, rot;

    if(fp_read==NULL){
        printf("Errore durante l'apertura del file '%s'.", filename);
        return NULL;
    }
    printf("File scacchiera '%s' caricato correttamente.\n\n", filename);
    fscanf(fp_read, "%d %d\n", nr, nc);
    // allocazione dinamica matrice (no free)
    matrix = malloc((*nr)*sizeof(box*));
    for(i=0; i<(*nr); i++){
        matrix[i] = malloc((*nc)*sizeof(box));
    }
    for(i=0; i<(*nr); i++){
        for(j=0; j<(*nc); j++){
            fscanf(fp_read, "%d/%d", &k, &rot);
            // caso cella vuota
            if(k==-1 && rot==-1){ 
                matrix[i][j].tile.vT1 = 0;
                matrix[i][j].tile.vT2 = 0;
                matrix[i][j].used = 0;
            }
            if(rot==1){
                matrix[i][j].tile = avTiles[k];
                matrix[i][j].used = 1;
                matrix[i][j].rot = 1;
                rotate(&(matrix[i][j]));
                avTiles[k].mark = 1;
            }
            if(rot==0){
                matrix[i][j].tile = avTiles[k];
                matrix[i][j].used = 1;
                matrix[i][j].rot = 0;
                avTiles[k].mark = 1;
            }
        }
    }
    fclose(fp_read);
    return matrix;
}

int main(void){
    int R, C, i, maxscore;
    tile *availableTiles = loadTiles(tFILENAME);
    box **matrix = loadMatrix(bFILENAME, availableTiles, &R, &C); 
    box **sol = malloc(R*sizeof(box*));
    for(i=0; i<C; i++){
        sol[i] = malloc(C*sizeof(box));
    }
    maxscore = disp_rip(0 , matrix, availableTiles, R, C, maxscore, &sol);
    printf("[+] Miglior punteggio: %d\n", maxscore);
    printBoard(sol,R,C);
    return 0;
}