#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s;
    int f;
    int d;
} att;


/*  Esercizio n. 1: Sequenza di attivita' (Versione 2)
? Problema: Trovare un sottoinsieme di attivita' compatibili  
? che massimizzi la somma delle durate utilizzando la programmazione dinamica

! Suggerimenti
* Si ordinino le attivita' lungo una linea temporale tenendo conto del fatto 
* che gli intervalli della soluzione non devono intersecarsi

* Si costruiscano soluzioni parziali considerando solamente le attiivta'
* fino all'i-esima dell'ordinamento definendo opportunamente il criterio
* secondo cui considerare le attivita'

* L’estensione di soluzioni parziali con l’introduzione di una
* attività aggiuntiva può essere fatta sulla base della compatibilità tra 
* la “nuova” i-esima attività e le soluzioni già note 
* ai problemi con le i-1 considerate precedentemente

* Seguire i passi: dimostrazione di applicabilita', calcolo ricorsivo del valore ottimo, 
* calcolo con programmazione dinamica bottom-up del valore e della soluzione ottima.
*/

void printAtt(att *a, int n){
    for(int i=0; i<n; i++){
        printf("(%d, %d) ", a[i].s, a[i].f);
    }
}

int max(int a, int b){
    if(a>=b)
        return a;
    else
        return b;
}

// ---------------------------------------------

// stampa ricorsiva
void aSDPrint(att *a, int *P, int i) {
    if (P[i]==-1) {
        printf("(%d, %d) ", a[i].s, a[i].f);
        return;
    }
    aSDPrint(a, P, P[i]);
    printf("(%d, %d) ", a[i].s, a[i].f);
}

// Ordinamento delle attivita' per orario di fine tramite insertion sort
// la soluzione sara' una sottosequenza della sequenza ordinata
// (una sottosequenza non ha indici necessariamente contigui)
void sortAtt(att* a, int n){
    int i, j, l=0, r=n-1;
    att x; 
    for (i = l+1; i <= r; i++) {
        x = a[i];
        j = i - 1;
        while (j >= l && x.f < a[j].f){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = x;
    }
}

/*
* La soluzione con programmazione dinamica trasforma quella ricorsiva in iterativa

- Passi:
* Il valore minimo di una sequenza è 1
* + per lunghezze crescenti del sottovettore considerato si individua 
* la sequenza che soddisfa le condizioni
* + si registra in P l'indice del valore precedente
* + stampa ricorsiva dei valore mediante eprcorrimento di P

* Calcolo del valore e della soluzione ottima (programmazione dinamica bottom-up)

* a: vettore di in put di N struct di tipo att
* sum: vettore di N interi per memorizzare la somma massima della sequenza per ogni prefisso i-esimo
* prev: vettore di N interi per memorizzare l'indice dell'elemento precedente nella sequenza
* last: int per memorizzare l'indice dell'ultimo elemento nella sequenza
*/

void attSelDynamic(att *a, int n) {
    int i, j, *sum, *prev, maxs = 0, last = 0;
    
    sum = calloc(n, sizeof(int));
    prev = calloc(n, sizeof(int));
    sum[0] = a[0].d;
    prev[0] = -1;

    // scorre le attivita 
    for (i = 1; i < n; i++) {
        sum[i] = a[i].d; // inizializza con durata dell'attivita corretne
        prev[i] = -1; // -1 indica nessuna attività precedente
        // scorre le attivita precedenti ad i per confrontarle con essa
        for (j = 0; j < i; j++) {
            if (a[i].s >= a[j].f || a[j].s >= a[i].f) {
                // se le attività i e j sono compatibili, calcola la somma massima
                if (sum[i] < a[i].d + sum[j]) {
                    sum[i] = a[i].d + sum[j]; prev[i] = j;
                }
            }
        }
        if (maxs <= sum[i]) {
            maxs = sum[i]; last = i;
        }
    }

    printf("[Versione dinamica] Somma massima: %d\n", maxs);
    printf("Sequenza ottima: ");
    while (last != -1) {
        printf("(%d, %d) ", a[last].s, a[last].f);
        last = prev[last];
    }
    free(sum);
    free(prev);
}

// soluzione ricorsiva -> calcola il valore ottimo della somma massima
int maxsR(att *a, int i) {
    int j, ris;
    // condizione di terminazione
    if (i==0)
        return a[i].d;
    // ricorsione
    ris = a[i].d;
    for (j=0; j < i; j++){
        // la condizione è che le attivita siano compatibili  
        if (a[i].s>=a[j].f || a[j].s>=a[i].f){
            ris = max(ris, a[i].d + maxsR(a, j));
        }
    }
    return max(ris, maxsR(a, i-1));
}

// wrapper
int maxs(att *val, int n) {
  return maxsR(val, n-1);
}

int main(void){
    att *attivita;
    int i, n;
    FILE *fp_read = fopen("att.txt", "r");
    if(fp_read==NULL){
        printf("Errore durante l'apertura del file.");
        return -1;
    }
    fscanf(fp_read, "%d", &n);
    printf("N: %d\nAttivita: ", n);
    attivita = malloc(n*sizeof(att));
    for(i=0; i<n; i++){
        fscanf(fp_read, "%d %d", &(attivita[i].s), &(attivita[i].f));
        attivita[i].d = attivita[i].f - attivita[i].s;
        printf("(%d, %d) ", attivita[i].s, attivita[i].f);
    }

    sortAtt(attivita, n);
    printf("\nSorted: ");
    printAtt(attivita, n);

    printf("\n[Versione ricorsiva] Somma massima: %d \n", maxs(attivita, n));
    attSelDynamic(attivita, n);
    fclose(fp_read);
    free(attivita);
    return 0;
}