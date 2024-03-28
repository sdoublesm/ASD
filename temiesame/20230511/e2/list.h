#ifndef LIST_H
#define LIST_h

#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct list *LIST;
typedef struct node *link;

struct node {
    Item val;
    link next;
};

void f(LIST l);
#endif