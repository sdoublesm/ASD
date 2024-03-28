#include "BST.h"

// determinare una funzione che, dato un BST, ne determini lo sbilanciamento, ovvero profondita massima - profondita minima
// creo BST come QUASI-ADT

struct binarysearchtree {link root; link z;};

// funzione ricorsiva
void calculate(link h, link z, int currval, int *min, int *max){
    if(h==z){
        if(currval>=*max)
            *max = currval;
        if(currval<=*min)
            *min = currval;
        return;
    }
    calculate(h->left, z, currval+1, min, max);
    calculate(h->right, z, currval+1, min, max);
}

//wrapepr
int sbilanciamento(BST b){
    int max=0, min=0, currmax=0, currmin=0;
    calculate(b->root, b->z, 0, &min, &max);
    return max-min;
}


// Impostare funzione oneChildCount che conta tutti i nodi che hanno uno ed un solo figlio

void count(link h, link z, int *cnt){
    // terminazione
    if(h==z){
        return;
    } 
    // ricorsione
    if((h->left==z & h->right!=z) || (h->right==z & h->left!=z)){
        (*cnt)++;
    }   
    count(h->left, z, cnt);
    count(h->right, z, cnt);
    return;
}

int oneChildCount(BST b){
    int cnt=0;
    count(b->root, b->z, &cnt);
    return cnt;
}