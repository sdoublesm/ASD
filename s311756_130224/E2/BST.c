#include "BST.h"

struct binarysearchtree {link root; link z;};

void generate(link x, link z, link *v, int *n){   
    if (x == z) 
        return;
    generate(x->left, z, v, n);
    v[*n] = x;
    (*n)++;
    generate(x->right, z, v, n);
}

link *BSTlevelizedNodes(BST b, int *n) {
    link *pnodes; int i;
    pnodes = malloc((*n)*sizeof(link));
    for(i=0; i<*n; i++)
        pnodes[i]=NULL;
    i=0;
    generate(b->root, b->z, pnodes, &i);
    return pnodes;
}
