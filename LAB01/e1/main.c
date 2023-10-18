#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Esercizio n. 1: Valutazione di espressioni regolari (regexp)
// si assume che le regexp vengano inserite correttamente dall'utente

// funzione ausiliaria che confronta i caratteri delle stringhe in entrata
// e ritorna il numero di caratteri da scorrere nella lettura della regex
int check(char *c2, char *c1) {
    // c1 from regexp, c2 from src
    int res = 0, i, flag=0;
    if (*c1 == *c2)
        res = 1;
    if (*c1 == '.' && isalnum(*c2) != 0)
        res = 1;
    if (*c1 == '\\' && *(c1 + 1) != '\0') {
        if (*(c1 + 1) == 'a' && islower(*c2))
            res = 2;
        if (*(c1 + 1) == 'A' && isupper(*c2))
            res = 2;
    }
    if(*c1=='[' && *(c1+1) != '\0' && strstr(c1, "]")!=NULL && *(c1+1)!=']'){ 
        // tutti i caratteri tra parentesi non sono ammessi
        if(*(c1+1)=='^' && *(c1+2)!=']'){
            res=1;
            for(i=2; *(c1+i)!=']'; i++){
                res++;
                if(*(c1+i)==*c2)
                    flag = 1;
            }
            if(flag==1)
                res=0;
            else
                res+=2;
        }
        // trova almeno un carattere contenuto nella parentesi
        if(*(c1+1)!='^'){
            for(i=1; *(c1+i)!=']'; i++){
                res++;
                if(*(c1+i)==*c2)
                    flag = 1;
            }
            if(flag==1)
                res+=2;
            else
                res=0;   
        }
    }
    return res;
}

char *cercaRegexp(char *src, char *regexp) {
    char *occ = NULL;
    int i, j, k=0, found=0;

    for (i = 0; src[i] != '\0'; i++) {
        j = 0;
        k = i;
        while (check((src + i), (regexp + j)) != 0 && regexp[j] != '\0' && found!=1) {
            j += check((src + i), (regexp + j));
            i++;
            if (regexp[j] == '\0') {
                occ = src + k;
                found = 1;
            }
        }
    }
    return occ;
}

int main(void) {
    char string[] = "siamo in uNa foto in moto";
    char regexp[] = "in [^klc]\\A. [ufs]ot.";  
    char *result;
    printf("---- regexp finder ----\nstring: %s\nregex: %s\n-----------------------\n", string, regexp);
    printf("results:\n");
    result = cercaRegexp(string, regexp);
    if(result==NULL){
        printf("no match found");
    }
    while(result!=NULL){
        printf("%s\n", result);
        result = cercaRegexp(result+1, regexp);
    }
    return 0;
}

