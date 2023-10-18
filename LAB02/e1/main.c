# include <stdio.h>

int gcd(int a, int b){
    int tmp;
    if(a<b){
        tmp = a;  a = b; b = tmp;
    }   

    // condizione di terminazione
    if(b==0)
        return a;

    if(a%2==0 && b%2==0)
        return(2*gcd(a/2, b/2));
    if(a%2!=0 && b%2==0)
        return(gcd(a, b/2));
    if(a%2==0 && b%2!=0)
        return(gcd(a/2, b));
    if(a%2!=0 && b%2!=0)
        return(gcd((a-b)/2, b));
}

int main(void){
    int a, b;
    printf("---- Ricerca MCM tramite algoritmo ricorsivo\n");
    printf("> Inserisci il primo numero intero positivo: "); scanf("%d", &a);
    printf("> Inserisci il secondo numero intero positivo: "); scanf("%d", &b);
    printf("- Massimo comun divisore tra %d e %d: %d", a, b, gcd(a, b));
    return 0;
}