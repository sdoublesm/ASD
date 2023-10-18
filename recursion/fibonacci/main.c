#include <stdio.h>
// ricorsione e numeri di fibonacci

unsigned long fib(int n) {
    // condizione di terminazione
    if(n == 0 || n == 1)
        return(n);
    return(fib(n-2) + fib(n-1));
}

int main(void){
    int n;
    printf("Inserisci n: ");
    scanf("%d", &n);
    printf("n-esimo numero della serie di fibonacci (n=%d): %lu", n, fib(n));
    return 0;
}