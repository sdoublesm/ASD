#ifndef SLIST_H
#define SLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {char name[16]; int val;} Item;
typedef struct node *link;
struct node {Item item; link next;};
typedef struct sl *SLIST;

#endif

