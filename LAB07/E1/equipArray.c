#include "equipArray.h"

struct equipArray_s {
    int *array;
    int n,max_n;
};

equipArray_t equipArray_init() {
    equipArray_t equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->n = 0;
    equipArray->max_n = EQUIP_SLOT;
    equipArray->array = malloc(EQUIP_SLOT * sizeof(int));
    return equipArray;
}

void equipArray_free(equipArray_t equipArray) {
    if(equipArray != NULL) {
        if(equipArray->array != NULL)
            free(equipArray->array);
        free(equipArray);
    }
}

int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->n;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;
    if(equipArray->n == 0) 
        return;

    fprintf(fp, "\nEquipaggiamenti:\n");
    for(i = 0; i<equipArray->n; i++) {
        invArray_printByIndex(fp,invArray,equipArray->array[i]);
        printf("\n");
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int i;
    if(equipArray->n >= equipArray->max_n) {
        printf("[Errore] SLOT PIENI\n");
        return;
    }

    printf("Equipaggiamenti disponibili:\n");
    invArray_print(stdout,invArray);

    printf("Scegli quale equipaggiamento aggiungere: ");
    scanf("%d",&i);
    equipArray->array[equipArray->n++] = i;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    if(index >= equipArray->n) {
        printf("[Errore] Equipaggio non esistente\n");
    }
    return(equipArray->array[index]);
}

stat_t equipArray_lastEquipStat(equipArray_t equip, invArray_t invArray) {
    printf("stat ultimo oggetto equipaggiato: %d %d\n\n", equip->n, equip->array[equip->n]);
    return invArray_getByIndex(invArray,equip->array[equip->n - 1])->stat;
}