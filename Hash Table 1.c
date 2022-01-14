#include <stdio.h>
#include <stdlib.h>
#define M 7 ///dimensiunea tabelei de dispersie


typedef struct cell
{
    int val;
    struct cell *next, *prev;
} NodeT;

int hFunction(int key)
{
    return key%M;
}

NodeT* search(NodeT* hTable[M], int key)
{
    NodeT *a=hTable[hFunction(key)];
    while(a)
    {

        if(a->val==key)
            return a;
        else
            a=a->next;
    }
    return NULL;
}

void insert(NodeT* hTable[M], int key)
{

    NodeT *a=(NodeT*)malloc(sizeof(NodeT));
    a->val=key;
    a->next=NULL;
    a->prev=NULL;
    if(hTable[hFunction(key)]==NULL)
        hTable[hFunction(key)]=a;
    else
    {
        a->prev=hTable[hFunction(key)];
        a->next=hTable[hFunction(key)];
        hTable[hFunction(key)]->prev=a;
        hTable[hFunction(key)]=a;
    }
}

void deleteKey(NodeT* hTable[M], int key)
{
    NodeT *a=search(hTable,key);

    if(a!=NULL && a!=hTable[hFunction(key)])
    {
        NodeT *b=a->prev;
        b->next=a->next;
        free(a);
    }
    else if(a!=NULL && a==hTable[hFunction(key)])
    {
        hTable[hFunction(key)]=a->next;
        free(a);
    }
    else if(a!=NULL)
    {
        hTable[hFunction(key)]=NULL;
        free(a);
    }
}

///afisarea tuturor elmentelor din tebela de dispersie
void showAll(NodeT* hTable[M])
{
    int i;
    for(i = 0; i < M; i++)
    {
        printf(" %d :",i);
        ///verificam daca la slotul i am adaugat ceva
        if(hTable[i] != NULL)
        {

            NodeT *p;
            p = hTable[i];
            while (p != NULL)
            {
                printf(" %d ",p->val);
                p = p->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{

    /// tabela de dispersie
    NodeT* hTable[M];
    int i, n,x;
    ///initializam tabelul nostru de dispersie
    for(i = 0; i < M; i++)
        hTable[i] = NULL;

    ///inseram un nou element in tabel
    insert(hTable, 1);
    insert(hTable, 2);
    insert(hTable, 3);
    insert(hTable, 4);
    insert(hTable, 5);
    insert(hTable, 6);
    insert(hTable, 7);
    insert(hTable, 8);

    ///afisam toate elementele
    showAll(hTable);
    ///stergere
    deleteKey(hTable, 1);
    deleteKey(hTable, 8);
    deleteKey(hTable, 4);

    ///afisam toate elementele din tabel din nou
    showAll(hTable);
    NodeT *f=search(hTable, 10);
    if(f==NULL)
        printf("exista in tabel de dispersie");
    else
        printf("nu exista in tabel de dispersie");
    return 0;
}

