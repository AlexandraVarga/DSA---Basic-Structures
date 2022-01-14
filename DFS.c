#include <stdio.h>
#include <stdlib.h>

/*****************************************************
  Citirea grafului se face din fisierul graf.txt;
  reprezentarea grafului este prin liste de adiacenta dinamice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge in maniera DFS si se salveaza arborele (arborii)
  de parcurgere, in vectorul pi; de asemenea, la varianta recursiva se
  inregistreaza si informatia de culoare si timpii de descoperire si
  finalizare (informatie mentinuta in structura grafului)
******************************************************/

typedef struct nod {
    int val;
    struct nod *next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT **t;  // tabloul de liste (va fi alocat dinamic)
    int *pi; //vectorul de parinti
    int *d; //timpii de descoperire
    int *f; //timpii de finalizare
    int *color; //informatia de culoare
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice; tine si informatia de parcurgere

enum {
    WHITE, GRAY, BLACK
};

void push(NodeT **stiva, int val) { //insert first in a linked list

    NodeT *el = (NodeT *) malloc(sizeof(NodeT));
    el->val = val;
    el->next = (*stiva);
    *stiva = el;
}

/* sterge elementul din varful stivei si returneaza valoarea lui */
int pop(NodeT **stiva)
{
    int n=-1;
    if(*stiva != NULL) {
        NodeT *firstElement = (*stiva);
        *stiva = (*stiva)->next;
        n=firstElement->val;
        free(firstElement);
    }
    return n;
}

/* returneaza 1 daca stiva este goala */
int empty(NodeT *stiva)
{
    return stiva == NULL;
}

void init(NodeT** stiva){
    *stiva = NULL;
}

void printErr() {
    printf("Memorie insuficienta!\n");
    exit(1);
}

//TODO implementati parcurgerea iterativa
void dfs_visit_iterativ(Graf *G, int start)
{
    NodeT* stiva;
    init(&stiva);
    push(&stiva,start);
    int parent=-1;
    G->pi[start]=parent;
    while (!empty(stiva))
    {
        int v=pop(&stiva);
        if (G->color[v] == WHITE)
        {
            G->color[v]=GRAY;
            printf("%d ",v);
            NodeT* w=G->t[v];
            while (w != NULL)
            {
                if (G->color[w->val] == WHITE)
                {
                    push(&stiva,w->val);
                    G->pi[w->val]=v;
                }
                w=w->next;
            }
        }
        G->color[v]=BLACK;
    }
}

void dfs_iterativ(Graf *G)
{
    int i;
    for (i = 0; i < G->n; i++)
        if (G->color[i] == WHITE)
            dfs_visit_iterativ(G, i);
}

void my_dfs_visit_iterativ(Graf *G, int start)
{
    NodeT* stiva;
    NodeT* stiva_aux;
    init(&stiva);
    push(&stiva,start);
    int parent=-1;
    G->pi[start]=parent;
    while (!empty(stiva))
    {
        int v=pop(&stiva);
        if (G->color[v] == WHITE)
        {
            G->color[v]=GRAY;
            printf("%d ",v);
            init(&stiva_aux);
            NodeT* w=G->t[v];
            while (w != NULL)
            {
                if (G->color[w->val] == WHITE)
                {
                    push(&stiva_aux,w->val);
                    G->pi[w->val]=v;
                }
                w=w->next;
            }
            while (!empty(stiva_aux))
            {
                int u=pop(&stiva_aux);
                push(&stiva,u);
            }
        }
        G->color[v]=BLACK;
    }
}

void my_dfs_iterativ(Graf *G)
{
    int i;
    for (i = 0; i < G->n; i++)
        if (G->color[i] == WHITE)
            my_dfs_visit_iterativ(G, i);
}


//int time = 0;
// TODO: Implementati dfs recursiv cu colorarea nodurilor si marcaje de timp
void dfs_visit(int v, Graf *G, int* time) {
    (*time)++;
    G->d[v]=(*time);
    G->color[v]=GRAY;
    printf("%d ",v);
    NodeT* w=G->t[v];
    while (w != NULL)
    {
        if (G->color[w->val] == WHITE)
        {
            G->pi[w->val]=v;
            dfs_visit(w->val,G,time);
        }
        w=w->next;
    }
    //printf("%d ",v);
    G->color[v]=BLACK;
    (*time)++;
    G->f[v]=(*time);
}

void dfs_recursiv(Graf *G) {

    int time = 0, i;

    for (i = 0; i < G->n; i++) {
        if (G->color[i] == WHITE) {
            dfs_visit(i, G, &time);
        }
    }
}


void citesteGraf(FILE *f, Graf *pG) {

    fscanf(f, "%d", &pG->n);  // citeste nr. de varfuri

    pG->t = (NodeT **) calloc(pG->n, sizeof(NodeT *));
    if (pG->t == NULL) printErr();  // alocare esuata

    pG->pi = (int *) calloc(pG->n, sizeof(int));
    pG->d = (int *) calloc(pG->n, sizeof(int));
    pG->f = (int *) calloc(pG->n, sizeof(int));
    pG->color = (int *) calloc(pG->n, sizeof(int));

    int i;
    for (i = 0; i < pG->n; i++) {
        pG->t[i] = NULL;
        pG->pi[i] = -1;
    }

    int v, w;
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        //graful va fi neorientat, se adauga atat arcul (v,w) cat si (w,v)
        push(&pG->t[w], v);
        push(&pG->t[v], w);
    }
}

void print(int* arr, int n)
{
    for(int i = 0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void reInitTraversalData(Graf *G)
{
    for(int i=0; i<G->n; i++)
    {
        G->d[i]     = -1;
        G->pi[i]    = -1;
        G->f[i]     = -1;
        G->color[i] = WHITE;
    }

}


int main() {
    FILE *f = fopen("graf.txt", "r");
    if (f == NULL) {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f, &G);
    fclose(f);

    //varianta iterativa
    printf("\n DFS varianta iterativa: ");
    dfs_iterativ(&G);
    printf("Vectorul de parinti: ");
    print(G.pi, G.n);

    reInitTraversalData(&G);
    //varianta iterativa in ordinea in care nodurile apar in lista de adiacenta
    printf("\n DFS varianta iterativa in ordine: ");
    my_dfs_iterativ(&G);
    printf("Vectorul de parinti in ordine: ");
    print(G.pi, G.n);

    reInitTraversalData(&G);
    //varianta recursiva
    printf("\n DFS varianta recursiva: ");
    dfs_recursiv(&G);
    printf("Vectorul de parinti:");
    print(G.pi, G.n);
    printf("Timpii de descoperire:");
    print(G.d, G.n);
    printf(" Timpii de finalizare:");
    print(G.f, G.n);


    //eliberam memoria
    free(G.color);
    free(G.d);
    free(G.f);

    int i;
    for (i = 0; i < G.n; i++) {
        /// TODO: eliberati nodurile din lista de adiacenta a lui i, daca e nevida
        if (G.t[i] != NULL)
            free(G.t[i]);
    }

    free(G.t);

    return 0;
}
