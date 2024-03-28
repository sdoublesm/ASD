#include <stdio.h>
#include <stdlib.h>
#define FILE_IN "elementi.txt"

typedef struct e_s {
    char name[100];
    int type, dir_in, dir_exit, prec, fin, diff;
    float val;
} elmnt;

/*
+ Esercizio n.2: Corpo libero

una serie di passaggi acrobatici
ogni serie e' composta da uno o più elementi
ogni elemento è descritto da una serie di parametri:
- nome dell'elemento stringa di max 100 caratteri
- tipologia: l'elemento può essere un elemento acrobatico di tipo avanti [2], 
indietro [1] o di transizione [0]
- direzione di ingresso: frontale [1] o di spalle [0]
- direzione di uscita: frontale [1] o di spalle [0]
- requisito di precedenza: può essere eseguito come primo [0] o deve essere preceduto
da almeno un altro elemento [1]
- finale: l'elemento puo essere seguito da altri elementi [1] o no [0]
- valore: il punteggio ottenuto per la corretta esecuzione di un elemento (num reale)
- difficolta: in un intero

elementi memorizzati in un file di testo

* Il ginnasta deve presentare 3 diagonali
* deve includere almeno un elemento acrobatico in ogni diagonale
* deve includere almento un elemento acrobatico avanti e almeno uno 
* indietro nel corso del programma (non necess. nella stessa diagonale)
* almeno una diagonale in cui compaiono almeno due elementi acrobatici in sequenza
* se il ginnasta include un elemento finale (con campo finale=0) di difficoltà 8 o superiore 
* nell'ultima diagonale,il punteggio complessivo della diagonale viene 
* moltiplicato per 1.5
* difficolta programma: somma delle diff delle diagonali
* il programma complessivamente non può avere difficoltà superiore a un dato valore DP

? Identificare la sequenza di diagonali che permettono al ginnasta di ottenere
? il punteggio più alto possibile, dato un set di elementi disponibili e 
? il valore dei due parametri DD e DP. 
*/

/*
! REGOLE DIAGONALI
* [x] perche due elementi possano essere eseguiti in sequenza, la direzione di 
* uscita del primo elemento deve coincidere con la direzione di ingresso del secondo elemento
* [x] si inizia sempre una diagonale frontalmente
* [x] ogni diagonale può contenere al massimo 5 elementi
* (difficolta diagonale: somma delle difficolta degli elementi)
* [x] ogni diagonale non può avere difficolta superiore ad un dato valore DD
*/

// funzione check promising
// deve calcolare somma delle difficolta in sol fino a pos corrente
// se è maggiore di DD non esegue piu nulla del ciclo for

int checkD(int pos, elmnt *val, elmnt *sol, int i, int DD){
    int psum=0;
    for(int j=0; j<=pos; j++){
        psum += sol[j].diff;
    }

    if((pos==0 && val[i].dir_in==1) || (pos!=0 && sol[pos-1].dir_exit == val[i].dir_in)){
        if(psum<DD){
            return 1;
        }
    }
    return 0;
}

/*
* utilizzo modello combinazioni ripetute 
* + condizione di pruning
mi serve funzione wrapper 
*/

int comb_r(int pos, elmnt* val, elmnt *sol, int n, int k, int start, int cnt, int DD, elmnt ***diags, int index){
    int i; elmnt *diag;
    if(pos>=k){
        diag = malloc(k * sizeof(elmnt));
        for(i=0; i<k; i++){
            diag[i] = sol[i];
            printf("%s | %d \n", sol[i].name, sol[i].diff);
        }
        (*diags)[index] = diag;
        printf("----------------\n");
        return cnt + 1;
    }
    for(i=start; i<n; i++){
        if(checkD(pos, val, sol, i, DD)==1){
            sol[pos] = val[i];
            cnt = comb_r(pos+1, val, sol, n, k, start, cnt, DD, diags, i);
        }
        start++;
    }
    return cnt;
}

// funzione wrapper che incrementi k da 1 a 5
int genDiags(elmnt *val, int n, int DD, elmnt ***diags, int maxDiags){
    elmnt *sol; int ncdiags = 0;
    for(int k=1; k<5; k++){
        sol = calloc(k, sizeof(elmnt));
        ncdiags += comb_r(0, val, sol, n, k, 0, 0, DD, diags, ncdiags)-1;
        free(sol);
        if (ncdiags >= maxDiags) {
            break;  // Stop generating diagonals if the limit is reached
        }
    }
    return ncdiags;
}

int main(void){
    elmnt *vettEl, **vettDiags; int n, i, DD, nDiags;
    FILE *fp_read = fopen(FILE_IN, "r");
    if(fp_read==NULL){
        printf("Errore durante l'apertura del file '%s'", FILE_IN);
    }
    fscanf(fp_read, "%d", &n);
    vettEl = malloc(n*sizeof(elmnt));
    int maxDiags = 400;  // Set a maximum number of diagonals
    vettDiags = malloc(maxDiags * sizeof(elmnt *));
    for (i = 0; i < maxDiags; i++) {
        vettDiags[i] = malloc(sizeof(elmnt));
    }

    for(i=0; i<n; i++){
        fscanf(fp_read, "%s %d %d %d %d %d %f %d\n", vettEl[i].name,
        &(vettEl[i].type), &(vettEl[i].dir_in), &(vettEl[i].dir_exit), &(vettEl[i].prec), &(vettEl[i].fin), &(vettEl[i].val), &(vettEl[i].diff));
    }
    fclose(fp_read);
    printf("Inserisci il valore DD: "); scanf("%d", &DD); getchar();

    printf("Generando le possibili diagonali con difficolta minore di %d...\n", DD);
    nDiags = genDiags(vettEl, n, DD, &vettDiags, maxDiags);
    for (i = 0; i < nDiags; i++) {
        free(vettDiags[i]);
    }
    free(vettDiags);
    free(vettEl);
    return 0;
}