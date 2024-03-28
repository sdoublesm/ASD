#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct list_t *LIST;
typedef struct node *link;

struct node {int val; link next;};

#endif
