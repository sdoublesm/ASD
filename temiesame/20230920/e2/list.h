#ifndef _LIST
#define _LIST

// ADT di I CLASSE per LIST
typedef struct list *LIST;
// QUASI-ADT per NODE
typedef struct node *link;

struct node {
    link prev;
    char val;
    link next;
};
#endif
