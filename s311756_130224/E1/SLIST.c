#include "SLIST.h"

struct sl {
    link head;
    int n;
};

link NEWnode(Item item, link next);
link sortedIns(link h, Item item);
SLIST SLISTmerge(SLIST a, SLIST b);

link NEWnode(Item item, link next) {
    link x = malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    else{
        x->item = item;
        x->next = next;
    }
    return x;
}

link sortedIns(link h, Item item){
    link x, p;
    if (h==NULL || strcmp(h->item.name, item.name)>0)
        return NEWnode(item, h);
    for (x=h->next, p=h; x!=NULL && strcmp(item.name, x->item.name)>0; p=x, x=x->next);
    p->next = NEWnode(item, x);
    return h;
}

SLIST SLISTmerge(SLIST a, SLIST b) {
    SLIST c;
    link x, y, toins;
    int f = 0;
    
    c = malloc(sizeof(*c));
    c->n = 0; c->head = NULL;
    
    for (x = a->head; x != NULL; x = x->next) {
        f = 0;
        for (y = c->head; y != NULL; y = y->next) {
            if (strcmp(x->item.name, y->item.name) == 0) {
                f = 1;
                y->item.val+=x->item.val;
            }
        }
        if (f == 0) {
            c->head = sortedIns(c->head, x->item);
            c->n++;
        } 
    }
    
    for (x = b->head; x != NULL; x = x->next) {
        f = 0;
        for (y = c->head; y != NULL; y = y->next) {
            if (strcmp((x->item).name, (y->item).name) == 0) {
                f = 1;
                y->item.val+=x->item.val;
            }
        }
        if (f == 0) {
            c->head = sortedIns(c->head, x->item);
            c->n++;
        }
    }
    return c;
}