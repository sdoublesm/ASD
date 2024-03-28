#include "TITLEs.h"

struct t {
    char name[MAXC];
    BST quot;
};

typedef struct node *link;
struct node {TITLE val; link next;};
struct LISTtitle { link head; int N; };
static link SortListIns(LISTtitle l, char new_data[],FILE *fp);
static link newnode(link head,char new_data[], FILE *fp);

LISTtitle readfile(FILE *fp, LISTtitle l){
    char nametitolo[MAXC];
    int dimensionetitoli;
    fscanf(fp,"%d\n",&dimensionetitoli);
    for(int i=0;i<dimensionetitoli;i++){
        fscanf(fp,"%s",nametitolo);
        ((l)->head)= SortListIns(l,nametitolo,fp);
    }
    printf("File caricato con successo.\n");
    return l;
}

LISTtitle LISTinit() {
    LISTtitle T = malloc(sizeof(LISTtitle));
    T->head = NULL;
    T->N = 0;
    return T;
}

TITLE TITLE_init() {
    TITLE T = malloc(sizeof(TITLE));
    T->quot=BSTinit();
    return T;
}

static link SortListIns(LISTtitle l, char new_data[], FILE *fp){
    link x,p;
    if((l->head)==NULL || maxkey(l->head->val->name, new_data)>0){
        l->N++;
        return newnode(l->head,new_data,fp);
    }
    for(x=(l->head)->next,p=(l->head);
        x!=NULL && maxkey(new_data, x->val->name)>0;
        p=x,x=x->next);
    p->next=newnode(x, new_data, fp);
    l->N++;
    return l->head;
}

int maxkey(char *a,char *b){
    return strcmp(a,b);
}

link newnode(link head,char new_data[],FILE *fp){
    struct node* new = (struct node*) malloc(sizeof(struct node));
    new->val = TITLE_init();
    strcpy(new->val->name,new_data);
    new->next=(head);
    readBST(&(new->val->quot),fp);
    return new;
}

void list_display(LISTtitle l){
    printf("\n");
    link tmp=l->head;
    if(tmp==NULL) printf("Non c'e' la lista\n");
    while((tmp)!=NULL){
        printf("%s\n",(tmp->val->name));
        treePrintW(tmp->val->quot);
        (tmp)=(tmp)->next;
    }
}

void searchTITLE(LISTtitle l){
    char searchTITLE[MAXC];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchTITLE);

    while(tmp!=NULL && maxkey(searchTITLE,tmp->val->name)>=0){
        if(strcmp(searchTITLE,tmp->val->name)==0){
            printf("Titolo trovato\n");
            printf("%s\n",(tmp->val->name));
            treePrintW(tmp->val->quot);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non e' presente nella lista\n");
}

void searchTITLEQuotationFromDate(LISTtitle l){
    char searchTITLE[MAXC];
    char date[11];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchTITLE);

    while(tmp!=NULL){
        if(strcmp(searchTITLE,tmp->val->name)==0 && maxkey(searchTITLE,tmp->val->name)>=0){
            printf("Titolo trovato\n");
            printf("Inserisci data: ");
            scanf("%s",date);
            searchBSTQuotationFromdate(tmp->val->quot,date);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo non e' presente nella lista\n");
}

void searchQuotfromRange(LISTtitle l){

    char searchTITLE[MAXC];
    char d1[11];
    char d2[11];
    link tmp=l->head;

    printf("Inserisci titolo da cercare: ");
    scanf("%s",searchTITLE);

    while(tmp!=NULL){
        if(strcmp(searchTITLE,tmp->val->name)==0 && maxkey(searchTITLE,tmp->val->name)<=0){
            printf("Titolo trovato|\n");
            printf("Inserisci prima data: ");
            scanf("%s",d1);
            printf("\nInserisci seconda data: ");
            scanf("%s",d2);
            searchBSTQuotationMINMAXFromRangeDate(tmp->val->quot, d1, d2);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo non e' presente nella lista\n");
}

void searchTITLEQuotationMINMAXFromAllPeriod(LISTtitle l){

    char searchTITLE[MAXC];
    link tmp=l->head;

    printf("Inserisci titolo da cercare: ");
    scanf("%s",searchTITLE);

    while(tmp!=NULL){
        if(strcmp(searchTITLE,tmp->val->name)==0 && maxkey(searchTITLE,tmp->val->name)<=0){
            printf("Titolo trovato!\n");
            searchBSTQuotationMINMAXFromAllPeriod(tmp->val->quot);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo non e' presente nella lista\n");
}

void balanceW(LISTtitle l){
    char searchTITLE[MAXC];
    link tmp=l->head;
    int maxheight, minheight, soglia;
    printf("Inserisci titolo da cercare: ");
    scanf("%s",searchTITLE);

    while(tmp!=NULL){
        if(strcmp(searchTITLE,tmp->val->name)==0 && maxkey(searchTITLE,tmp->val->name)<=0){
            printf("Titolo trovato!\n");
            printf("Inserisci valore soglia S: ");
            scanf("%d",&soglia);
            maxheight=altezzaBSTmaxW(tmp->val->quot);
            minheight=altezzaBSTminW(tmp->val->quot);
            if(maxheight/minheight > soglia){
                printf("Altezza finale: %d:\nAltezza minima: %d \n",maxheight-1,minheight-1);
                BalanceBST(tmp->val->quot);
            }else {
                printf("Bilanciamento BST non necessario.\n");
            }
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo non e' presente nella lista\n");
}

void TITLEfree(TITLE t){
    BSTQUOTfree(t->quot);
}

void LISTfree(LISTtitle l){
    link x, y,tmp;
    for(x = l->head; x != NULL; x = y){
        tmp=x;
        y = x->next;
        TITLEfree(tmp->val);
        free(tmp);
    }
    free(l);
}