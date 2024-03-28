#include <stdio.h>
#include <stdlib.h>

typedef struct edge {int v; int wt; int w;} Edge;
typedef struct graph *Graph;
struct graph {int V; int E; int **madj; int *tab;};
// -------------------------------------- ST st-> tabella di simboli che associa nome a indice della tabella

// determinazione cammino di hamilton
void hamilton(){
    // serve vettore visited + counter! i vertici visitati devono essere esattamente V-1
    // terminazione v==w -> arrivato + check counter = v-1
    // ricorsione -> per ogni vertice t adiacente a v ricorro e incremento il counter
}

// stessa cosa cammino semplice ma senza condizione su v-1 nella terminazione


// visita in ambiezza BFS a partire da un vertice sorgente s -> NON visita necessariamente tutti i vertici
// estrae un ARCO (vertice) dalla coda e mette in coda tutti gli archi verso i vertici adiacenti non ancora
// scoperti aggiornando il tempo di scoperta nel vettore time e il padre
// si inizia da un singolo vertice id -> e = (id, id)

void bfs(Graph G, Edge e, int *time, int *visited, int* p, int *dist){
    // e arco di partenza
    Q q = Qinit(); // inizializzo queue
    Qput(q, e);
    dist[e.v] = -1;
    while(!isEmpty(q)==0){ // fino a che la coda non e vuota
        e = qGet(q); // estrai il vertice dalla coda
        if(visited[e.w]==-1){ // se non è stato visitato
            visited[e.w] = *time; // visita-> registra tempo scoperta
            *time+=1; // incrementa tempo
            p[e.w] = e.v; // registra predecessore
            dist[e.w] = dist[e.v]+1; // incrementa distanza dal vertice di partenza
            for(int x=0; x<G->V; x++){ 
                if(G->madj[e.w][x]==1){ // per ogni vertice adiacente x
                if(time[x]==-1){
                    Qput(q, edgeCREATE(e.w, x)); // inserisci nela coda a priorita l'arco da w a x
                }
                }
            }
        }
    }
}

// DFS
void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *p){
    link t;
    int v,, w = e.w;

}
