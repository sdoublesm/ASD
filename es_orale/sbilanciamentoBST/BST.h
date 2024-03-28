#include <stdio.h>
#include <stdlib.h>

typedef struct binarysearchtree *BST;
typedef struct node *link;

struct node {int val; link left; link right;};

void calculate(link h, link z, int currval, int *min, int *max);
int sbilanciamento(BST b);
void count(link h, link z, int *cnt);
int oneChildCount(BST b);