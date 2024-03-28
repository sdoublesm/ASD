#include "list.h"

struct list {
    link head;
    int N;
};

void f(LIST l){
    link x, tmp;
    for(x=l->head; x!=NULL; x=x->next){
        if(x->val == x->next->val){
            if(x->next->next!=NULL)
                x->next = x->next->next;
            else
                x->next = NULL;
        }
    }
}