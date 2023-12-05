#include <stdio.h>
#include <stdlib.h>

// determinare il massimo nunmero di abitanti copribile rispettando la regola 

// in ogni citta si puo installare un'antenna alla condizione che 
// le citta adiacenti (precedente e successiva) non abbiano non abbiano l'antenna

// Problema di ottimizzazione -> modello del powerset per determinare i 
// sottoinsiemi delle antenne

// Altrimenti -> programmazione dinamica
// vettore val di n+1 celle

// se nella città k non c'è una antenna la soluzione ottima corrisponde
// con quella ottenuta per le prime k-1 citta

// se nella citta k c'è un'antenna
// la soluzione ottima è quella delle prime k-2 citta + l'antenna della citta k

// abbiamo un vettore opt di n+1 celle scandito da indice k


// soluzione ricorsiva
int solveR(int *val, int *opt, int n, int k){
    if(k==0){
        return 0;
    }
    if(k==1){
        return val[k];
    }
    return max(solveR(val, opt, n, k-1), solveR(val, opt, n, k-2));
}

// soluzione con programmazione dinamica
// si trasforma in forma interativa la soluzione ricorsiva
// opt[0] e opt[1] sono inizializzati a priori
// per 2<=i<=n, opt[i] = max(opt[i-1], opt[i-2]+val[i])

int main(void){
    
    return 0;
}