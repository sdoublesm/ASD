#ifndef TITLES_H
#define TITLES_H

#define MAXC 21
#include "datetime.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "quot.h"

typedef struct t *TITLE;
typedef struct LISTtitle *LISTtitle;

LISTtitle readfile(FILE *fp,LISTtitle l);
int maxkey(char *a,char *b);
LISTtitle LISTinit();
void list_display(LISTtitle l);
TITLE TITLE_init();
void searchTITLE(LISTtitle l);
void searchTITLEQuotationFromDate(LISTtitle l);
void searchQuotfromRange(LISTtitle l);
void searchTITLEQuotationMINMAXFromAllPeriod(LISTtitle l);
void balanceW(LISTtitle l);
void TITLEfree(TITLE t);
void LISTfree(LISTtitle l);
#endif