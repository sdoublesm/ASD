#include "BST.h"

struct binarysearchtree {
    link root;
    link z;
};

/*
Si scriva una funzione (wrapper) int f(BT t) che ricevuto in input un 
albero binario di interi t di tipo BT verifichi se questo rappresenti o meno un BST.

! ERRORE 
! Proprieta del BST verificata solo rispetto alla terna radice, 
! figlio sinistro, figlio destro, anziche rispetto all’intero sottoalbero
! radicato a sinistra/destra.
*/

int isBST(link h, link z){
    int max_left, min_right;
    // condizione di terminazione
    if(h == z){
        return 1;
    }
    // devo stabilire il massimo del sottoalbero sinistro
    // e il minimo del sottoalbero destro tra cui il valore del
    // nodo corrente deve essere compreso
    max_left = max(h->left);
    min_right = min(h->right);
    if (max_left > h->val || min_right < h->val)
        return 0;
        
    if (isBST(h->left, z) && isBST(h->right, z))
        return 1;
    return 0;
}

int f(BST t){
    return isBST(t->root, t->z);
}