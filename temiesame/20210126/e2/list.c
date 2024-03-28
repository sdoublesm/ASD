
#include "list.h"

struct list_t {int n; link head};
void f(LIST l, int *v, int n);

void f(LIST l, int *v, int n){
    int i, f; 
    link x, tmp;
    for(x=l->head; x->next != NULL; x = x->next){
        f=0;
        for(i=0; i<n; i++){
            if(v[i]==x->next->val){
                f=1;
            }
        }
        if(f==0){
            x->next = x->next->next;
        }
    }
}

