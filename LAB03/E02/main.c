#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHARS 256
#define FILENAME "brani.txt"

// Esercizio n. 2: Playlist
// Utilizzo del principio di moltiplicazione

typedef struct{
    char **scelte;
    int num_scelte;
} Livello;

int princ_molt(int pos, Livello *val, char **sol, int k, int count) {
  int i;
  if (pos >= k) {  // condizione di terminazione
    printf("> [PLAYLIST %d]\n ", count+1);
    for (i = 0; i < k; i++) 
      printf("%s; ", sol[i]);  
    printf("\n");
    return count+1; // numero soluzioni trovate
  }
  for (i = 0; i < val[pos].num_scelte; i++) {
    strcpy(sol[pos], val[pos].scelte[i]); // aggiungo alla soluzione attuale il valore di ogni scelta possibile
    count = princ_molt(pos+1, val, sol, k, count); // chiamata ricorsiva
  }
  return count;
}

int main(void){
    Livello *val; 
    char **sol; 
    int pos=0, count=0, nf, i, j;
    FILE *fp_read=fopen("brani.txt", "r");

    if(fp_read==NULL){
        printf("[!] Errore durante l'apertura del file");
        return -1;
    }

    fscanf(fp_read, "%d", &nf);

    // Allocazione dinamica strutture dati
    val = malloc(nf*sizeof(Livello)); // vettore di struct Livello di dimensione n che contiene TUTTE le SCELTE
    // ogni struct contiene un numero di scelte per quel livello
    sol = malloc(nf*sizeof(char*)); // vettore di stringhe che contiene una soluzione
    for(i=0; i<nf; i++){
        sol[i] = malloc(MAXCHARS*sizeof(char));
    }

    for(i=0; i<nf; i++){
        fscanf(fp_read, "%d", &val[i].num_scelte); // per ogni amico ho un numero di scelte possibili
        val[i].scelte = malloc(val[i].num_scelte*sizeof(char*)); // inizializzo vettore contenente i titoli
        for(j=0; j<val[i].num_scelte; j++){
            val[i].scelte[j] = malloc(MAXCHARS*sizeof(char));
            fscanf(fp_read, "%s", val[i].scelte[j]);
        }
    }

    printf("+ Generazione playlist dal file '%s':\n",FILENAME );
    count = princ_molt(pos, val, sol, nf, count);
    printf("+ Numero di combinazioni possibili: %d\n", count);

    free(val->scelte);
    free(val);
    for(i=0; i<nf; i++)
        free(sol[i]);
    free(sol);
    return 0;
}