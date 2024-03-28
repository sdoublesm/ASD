#include <stdio.h>
#include "list.h"

struct list {
    link head;
    int N;
};

/*
Si fornisca la definizione delle strutture dati LIST e NODE, 
come ADT di I categoria e quasi ADT
rispettivamente, per rappresentare una lista doppio linkata di caratteri, 
senza sentinelle. Suddividere
il codice in modo opportuno tra file .h e .c
Si scriva una funzione void f(LIST l, int k) che ricevuta in input una lista 
rappresentata facendo riferimento ai tipi definiti in precedenza, 
già ordinata in ordine alfabetico crescente, compatti
i contenuti della lista cancellando tutti i nodi uguali consecutivi, 
ad eccezione del primo di ogni gruppo, solo se la sotto-lista di nodi 
uguali consecutivi è composta k da almeno elementi.
*/

void f(LIST l, int k){
    link x, tmp;
    if(l->N>=k){
        for(x=l->head; x!=NULL; x=x->next){
            if(x->val == x->next->val){
                tmp = x->next;
                x->next = tmp->next;
                x->next->prev = x;
            }
        }
    }
}