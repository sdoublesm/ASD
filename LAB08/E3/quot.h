#ifndef QUOT_H
#define QUOT_H

#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    datetime data;
    float valore;
    int ntrans;
} quot;

typedef struct  binarysearchtree *BST;

quot quotsetNull();
BST BSTinit();
quot quotScan(FILE *fp);
void BSTinsert_leafI(BST bst, quot x);
void readBST(BST *bstq,FILE *fp);
void QuotationStore(quot val);
void BSTsearch(BST bst, quot k);
void treePrintW(BST bstq);
void editnodebst(quot *item, quot k);
void searchBSTQuotationFromdate(BST bst,char *date);
void searchBSTQuotationMINMAXFromRangeDate(BST bst,char *date1,char *date2);
void searchBSTQuotationMINMAXFromAllPeriod(BST bst);
void BalanceBST(BST bst);
int altezzaBSTmaxW(BST bst);
int altezzaBSTminW(BST bst);
void BSTQUOTfree(BST bst);
#endif