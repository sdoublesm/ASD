#include <stdio.h>
#include <stdlib.h>

typedef enum {zaffiro, rubino, topazio, smeraldo} pietra;

// SISTEMARE !!!!!!!

// Verifica di accettabilita' della soluzione
// -> verifica che sia possibile ottenere una collana con le specifiche
// caratteristiche a partire dal vettore contenente il numero di pietre disponibili 
int check(int *npietre, pietra *sol, int k) {
    int i, used[] = {0, 0, 0, 0};
    pietra p;

    // Scorre il vettore sol utilizzando una pietra alla volta
    for (i = 0; i < k; i++) {
        p = sol[i];
        used[p]++;
        if (used[p] > npietre[p])
            return 0;

        if (i != 0) {
        if (((sol[i-1]==zaffiro) || (sol[i-1]==topazio)) && (sol[i]!=zaffiro) && (sol[i]!=rubino))
            return 0;
        if (((sol[i-1]==smeraldo) || (sol[i-1]==rubino)) && (sol[i]!=smeraldo) && (sol[i]!=topazio))
            return 0;
        }
    }
    return 1;
}

// k è assegnato iterativamente

// Modifico la funzione in modo che indichi un successo
// o un fallimento nella costruzione della collana
// Gli passo il vettore contenente il numero di pietre

// SOL ha lunghezza k e contiene le pietre in sequenza

// IMPORTANTE OSSERVAZIONE PRUNING:
// la prima catena più lunga ha sempre in fila tutti zaffiri 
// e tutti smeraldi appena ne incontra uno
int disp_rip(int pos, int *npietre, pietra *sol, int n, int k) {
    pietra i;

    // Condizione di terminazione
    // INCLUDO LA CONDIZIONE DI ACCETTABILITA'
    if (pos >= k) {
        if (check(npietre, sol, k) == 1)
            return 1;
        return 0;
    }

    // Ricorsione
    for (i = zaffiro; i <= smeraldo; i++) {
        sol[pos] = i;
        if (disp_rip(pos + 1, npietre, sol, n, k) == 1)
            printf("[YES] sol[pos]: %d\n", sol[pos]);
            return 1;
    }
    return 0;
}

// Calcolare una delle lunghezze massime della sequenza

// NOTA: la lunghezza della soluzione non è nota a priori, 
// ma può variare tra 1 e (z+r+t+s).
// COME GESTISCO k? <- obiettivo
// Devo iterare, chiamando disp_rip che contiene la verifica
// e mi dà l'ok sull'avvenuta creazione della collana con
// lunghezza k -> lunghezza massima possibile alla fine del ciclo 
int main() {
    int i, k, pos = 0, n = 4, bestk = 0, maxk = 0, avpietre[n];
    pietra *sol;
    char p[] = {'z', 'r', 't', 's'};
    
    // Esempio set: 2 1 2 2 
    // maxk = somma di questi valori
    // bestk (il max possibile) è l'obiettivo 
    int numpietre[] = {1, 3, 7, 1}; // Esempio set

    for (i = 0; i < n; i++) {
        maxk += numpietre[i];
    }
    sol = calloc(maxk, sizeof(pietra));
    for (k = 1; k <= maxk; k++) {
        for (i=0; i<n; i++)
            avpietre[i]=numpietre[i];
        // disp_rip riempie il vettore sol
        if (disp_rip(pos, avpietre, sol, n, k) == 1) {
            bestk = k;
        }
    }
    printf("UNA BEST LUNGHEZZA PER IL SET: %d\n", bestk);
    for (i = 0; i < bestk; i++)
        printf("%c", p[sol[i]]);
    printf("\n");

    free(sol);

    return 0;
}
