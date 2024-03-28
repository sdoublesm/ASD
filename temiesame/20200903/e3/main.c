#include <stdio.h>
#include <stdlib.h>

/*
nS sale 
vettore S[nS] contiene le capienze di ogni sala
nP gruppi che prenotano
P[nP] contiene cardinalita di ogni gruppo

? Si scriva un algoritmo ricorsivo in grado di 
? determinare, se esiste, un’assegnazione delle prenotazioni
? ricevute nelle sale del locale, tale per cui il numero di sale occupate 
? sia minimo.

ti servirebbe un vettore di capienzeUsate e un bestCapienze usate
che uso nel wrapper e uso per il controllo

  for(sala=0; sala<nS; sala++){
      if(capienzeUsate[sala]+P[pos] > S[sala]) continue;
      sol[pos]=sala;
      capienzeUsate[sala]+=P[pos];
      dispRip(S, nS, P, nP, capienzeUsate, sol, bestSol, bestCapienze, min, pos+1);
      capienzeUsate[sala]-=P[pos];

*/


disp_rip

//wrapper
void solve(int *S, int nS, int *P, int nP, ...){

}


int main(void){
    return 0;
}