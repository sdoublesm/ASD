#include "pg.h" // a sua volta include inventario.h

/*
Si scriva un programma in C che permetta di:
* [x] caricare in una lista l’elenco di personaggi
* [x] caricare in un vettore di strutture, allocato dinamicamente, l’elenco di oggetti 
* [x] aggiungere un nuovo personaggio 
* [x] eliminare un personaggio 
* [ ] aggiungere/rimuovere un oggetto dall’equipaggiamento di un personaggio 
* [ ] calcolare le statistiche di un personaggio tenendo in considerazione i suoi 
* parametri base e l’equipaggiamento corrente, applicando quindi i bonus e 
* i malus dell'equipaggiamento stesso. Se una certa statistica risultasse 
* inferiore a 0 in seguito all'applicazione dei malus, in fase di visualizzazione 
* si stampi 0, per convenzione, anziché il valore negativo 
* assunto dalla statistica stessa. 
*/


int main(void){
    tabObj *tabObjects = malloc(sizeof(tabObj));
    tabPG *tabPers = malloc(sizeof(tabPG));

    tabObjects = loadObjects("inventario.txt");
    tabPers = loadPGs("pg.txt");
    printList(tabPers->headPG);
    printf("OK");
    addObj(&(tabPers->headPG->val), tabObjects);
    printList(tabPers->headPG);


    return 0;
}