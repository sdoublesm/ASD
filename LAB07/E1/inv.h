#ifndef INV_H_defineD
#define INV_H_defineD

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 100
#define MIN_STAT 1

/* quasi ADT statistiche */
typedef struct stat_s {
  int hp, mp, atk, def, mag, spr;
} stat_t;

/* quasi ADT oggetto di inventario */
typedef struct inv_s {
  char nome[LEN];
  char tipo[LEN];
  stat_t stat;
} inv_t;

void stat_read(FILE *fp, stat_t *statp);
void stat_print(FILE *fp, stat_t *statp, int soglia);
void inv_read(FILE *fp, inv_t *invp);
void inv_print(FILE *fp, inv_t *invp);
stat_t inv_getStat(inv_t *invp);

#endif
