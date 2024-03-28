#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct binarysearchtree *BST;

typedef struct BSTnode *link;
struct BSTnode {
    Item val;
    link left;
    link right; 
};
#endif