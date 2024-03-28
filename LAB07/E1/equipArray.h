#ifndef EQUIPARRAY_H_DEFINED
#define EQUIPARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

typedef struct equipArray_s *equipArray_t; 

equipArray_t equipArray_init();
void equipArray_free(equipArray_t equipArray);
int equipArray_inUse(equipArray_t equipArray);
void equipArray_print(FILE *fin, equipArray_t equipArray, invArray_t invArray);
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray);
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index);
stat_t equipArray_lastEquipStat(equipArray_t equip, invArray_t invArray);

#endif
