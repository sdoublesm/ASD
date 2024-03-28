#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct binarysearchtree *BST;
typedef struct node *link;
struct node {int val; link left; link right;};

#endif