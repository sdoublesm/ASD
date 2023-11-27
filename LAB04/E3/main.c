#include <stdio.h>
#include <stdlib.h>

typedef enum {zaffiro, rubino, topazio, smeraldo} pietra;

// Calcolare una delle lunghezze massime della sequenza

// NOTA: la lunghezza della soluzione non è nota a priori, 
// ma può variare tra 1 e (z+r+t+s).
// COME GESTISCO k? <- obiettivo

// Idea di base: utilizzo del main come 'wrapper'
// Devo iterare, chiamando disp_rip che contiene la verifica
// e mi dà l'ok sull'avvenuta creazione della collana con
// lunghezza k -> lunghezza massima possibile alla fine del ciclo 

// Verifica di accettabilita' della soluzione
// -> verifica che sia possibile ottenere una collana con le specifiche
// caratteristiche a partire dal vettore contenente il numero di pietre disponibili 
int check(int *npietre, pietra *sol, int k) {
    int i, used[4] = {0, 0, 0, 0};
    pietra p;

    // Scorre il vettore sol utilizzando una pietra alla volta
    for (i = 0; i < k; i++) {
        p = sol[i];
        used[p]++; // ad ogni iterazione, sol[i] contiene int corrispondente alla pietra 
        if (used[p] > npietre[p])
            return 0;
        if (i != 0) {
            if (((sol[i-1]==zaffiro) || (sol[i-1]==topazio)) && ((sol[i]!=zaffiro) && (sol[i]!=rubino)))
                return 0;
            if (((sol[i-1]==smeraldo) || (sol[i-1]==rubino)) && ((sol[i]!=smeraldo) && (sol[i]!=topazio)))
                return 0;
        }
    }
    return 1;
}

// Modifico la funzione in modo che indichi un successo
// o un fallimento nella costruzione della collana
// Gli passo il vettore contenente il numero di pietre

// SOL ha lunghezza k e contiene le pietre in sequenza

// IMPORTANTE OSSERVAZIONE PRUNING:
// la prima catena più lunga ha sempre in fila tutti zaffiri 
// e tutti smeraldi appena ne incontra uno

int disp_rip(int pos, int *npietre, pietra *sol, int n, int k, pietra *bestsol) {
    int i, j;

    // Condizione di terminazione
    if (pos >= k) {
        if (check(npietre, sol, k) == 1) {
            printf("[DBG] LUNGHEZZA SET: %2.d\n", k);
            for (j = 0; j < k; j++) {
                printf("[DBG] sol[%.2d] = %d\n", j, sol[j]);
                bestsol[j] = sol[j];
            }
            return 1;
        }
        return 0;
    }

    // Ricorsione
    for (i = 0; i < n; i++) {
        // Pruning: inserisce nel vettore soluzione tutti gli zaffiri e gli smeraldi
        // disponibili quando ne incontra uno
        if ((i == 0 || i == 3)) {
            if (pos + npietre[i] <= k) {
                for (j = 0; j < npietre[i]; j++) {
                    sol[pos + j] = i;
                }
                if (disp_rip(pos + npietre[i], npietre, sol, n, k, bestsol) == 1) {
                    return 1;
                }
            }
        } else {
            sol[pos] = i;
            if (disp_rip(pos + 1, npietre, sol, n, k, bestsol) == 1) {
                return 1;
            }
        }
    }
    return 0;
}


int main() {
    int i, k, n = 4, bestk = 0, maxk = 0;
    pietra *sol, *bestsol;
    
    // maxk = somma di questi valori
    // bestk (il max possibile) è l'obiettivo 
    int numpietre[] = {7, 7, 4, 2}; // Esempio set
    char p[] = {'z', 'r', 't', 's'};
    for (i = 0; i < n; i++) {
        maxk += numpietre[i];
    }

    bestsol = calloc(maxk, sizeof(pietra));

    for (k = 1; k <= maxk; k++) {
        sol = calloc(k, sizeof(pietra));
        // disp_rip -> finisce col riempire il vettore sol
        // con la soluzione migliore
        if (disp_rip(0, numpietre, sol, n, k, bestsol) == 1) {
            bestk = k;
        free(sol);
        }
    }
    printf("\nSet costituito da:\n");
    printf("%d zaffiri, %d rubini, %d topazi e %d smeraldi\n", numpietre[0], numpietre[1], numpietre[2], numpietre[3]);
    
    printf("Una delle lunghezze massime per il set e': %d\nSequenza: ", bestk);
    for (i = 0; i < bestk; i++)
        printf("%c ", p[bestsol[i]]);
    printf("\n");

    free(bestsol);

    return 0;
}
