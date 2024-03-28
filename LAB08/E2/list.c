#include "list.h"

struct list{int V; int E; link *ladj; ST tab; link z;};

static link NEW(int v,int wt, link next);
static edge_l edgeCreate(int v, int w, int wt);
static void insertL(LIST L, edge_l e);

static link NEW(int v, int wt, link next){
    link x=malloc(sizeof *x);
    if(x==NULL) 
        return NULL;
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

static edge_l edgeCreate(int v, int w, int wt){
    edge_l e;
    e.v=v; e.w=w; e.wt=wt;
    return e;
}

LIST LISTinit(int V){
    int v;
    LIST l = malloc(sizeof *l);
    l->V = V;
    l->E = 0;
    l->z = NEW(-1, 0, NULL);
    if (l->z == NULL)
        return NULL;
    l->ladj = malloc(l->V*sizeof(link));
    if (l->ladj == NULL)
        return NULL;
    for (v = 0; v < l->V; v++)
        l->ladj[v] = l->z;
    l->tab = STinit(V);
    if (l->tab == NULL)
        return NULL;
    return l;
}

void LISTfree(LIST l){
    int v;
    link t, next;
    for(v=0;v< STsize(l->tab);v++){
        for(t=l->ladj[v];t!=l->z;t=next){
            next=t->next;
            if(t!=NULL) free(t);
        }
    }
    STfree(l->tab);
    free(l->ladj);
    free(l->z);
    free(l);
}

void LISTedges(LIST l, edge_l *a){
    int v,E=0;
    link t;
    for(v=0;v< STsize(l->tab);v++){
        for(t=l->ladj[v]; t!=l->z; t=t->next){
            a[E++]= edgeCreate(v,t->v,t->wt);
        }
    }
}

void LISTinsertL(LIST l, int id1, int id2, int wt){
    insertL(l, edgeCreate(id1, id2, wt));
}

static void insertL(LIST l, edge_l e) {
    int v = e.v, w = e.w, wt = e.wt;
    l->ladj[v] = NEW(w, wt, l->ladj[v]);
    l->E++;
}

void LISTcheckADJ(LIST L){
    char v1[MAXCL],v2[MAXCL],v3[MAXCL];
    int i1, i2, i3, cntadj=0;
    link t;

    printf("Inserisci i nomi dei tre vertici da vertificare: \n");
    scanf("%s %s %s",v1,v2,v3);

    i1 = STgetIndex(L->tab,v1);
    i2 = STgetIndex(L->tab,v2);
    i3 = STgetIndex(L->tab,v3);int i;

    for(t=L->ladj[i1]; t!=L->z; t=t->next) 
        if(t->v==i2) 
            cntadj++;

    for(t=L->ladj[i2]; t!=L->z; t=t->next) 
        if(t->v==i3) 
            cntadj++;

    for(t=L->ladj[i3]; t!=L->z; t=t->next) 
        if(t->v==i1) 
            cntadj++;

    if(cntadj==3) 
        printf("I vertici sono adiacenti.\n");
    else 
        printf("I vertici NON sono adiacenti.");
}