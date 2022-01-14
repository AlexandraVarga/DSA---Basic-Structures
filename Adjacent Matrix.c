#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    int** m;
}Graph;

typedef struct node
{
    int key;
    struct node* next;
}NodeT;

typedef struct
{
    NodeT* head;
    NodeT* tail;
}queue;

queue createEmpty(queue Q)
{
    Q.head = NULL;
    Q.tail = NULL;
    return Q;
}

int isEmpty(queue Q)
{
    if (Q.head == NULL && Q.tail == NULL)
        return 1;
    else
        return 0;
}

queue enqueue(int key, queue Q) /// insert_last
{
    NodeT* newNode=(NodeT*)malloc(sizeof(NodeT));
    newNode->next=NULL;
    newNode->key=key;
    if(isEmpty(Q))
    {
        Q.head=newNode;
        Q.tail=newNode;
    }
    else
    {
        Q.tail->next=newNode;
        Q.tail=newNode;
    }
    return Q;
}

queue dequeue(queue Q) /// delete_first
{
    if(isEmpty(Q))
        return createEmpty(Q);
    NodeT* p=Q.head;
    Q.head=Q.head->next;
    free(p);
    if(Q.head == NULL)
        Q.tail=NULL;
    return Q;
}

void printQueue(queue Q)
{
    NodeT* p;
    p=Q.head;
    printf("Q: ");
    while (p != NULL)
    {
        printf("%d ",p->key);
        p=p->next;
    }
    printf("\n");
}

enum{NEVIZITAT,VIZITAT};

void BFS(Graph G, int source, FILE* f)
{
    int n=G.n;
    int visit[n];
    queue Q;
    Q=createEmpty(Q);
    for (int i=0;i<n;i++)
        visit[i]=NEVIZITAT;
    visit[source]=VIZITAT;
    fprintf(f,"BFS(G,%d): %d ",source,source);
    Q=enqueue(source,Q);
    while (isEmpty(Q)==0)
    {
        int v=Q.head->key;
        Q=dequeue(Q);
        for (int i=0;i<n;i++)
            if (*(*(G.m+v)+i)!=0)
            {
                if (visit[i]==NEVIZITAT)
                {
                    visit[i]=VIZITAT;
                    fprintf(f,"%d ",i);
                    Q=enqueue(i,Q);
                }
            }
    }
    printf("\n");
}

int main()
{
    Graph G;
    Graph D;
    FILE* f=fopen("graph_file.txt","r");
    if (f == NULL)
    {
        printf("Error\n");
        exit(1);
    }
    fscanf(f,"%d",&G.n);
    D.n=G.n;
    G.m=(int**)calloc(G.n,sizeof(int*));
    if (G.m != NULL)
        for (int i=0;i<G.n;i++)
            G.m[i]=(int*)calloc(G.n,sizeof(int));
    D.m=(int**)calloc(D.n,sizeof(int*));
    if (D.m != NULL)
        for (int i=0;i<D.n;i++)
            D.m[i]=(int*)calloc(D.n,sizeof(int));
    int x,y;
    while (1)
    {
        if (fscanf(f,"%d%d",&x,&y) != 2)
            break;
        *(*(G.m+x)+y)=1; /// consider G graf neorientat
        *(*(G.m+y)+x)=1;
        *(*(D.m+x)+y)=1; /// consider D graf orientat
    }
    fclose(f);
    printf("Number of vertices = %d\n",G.n);
    /// Neorientat:
    printf("\nAdjacency matrix(G):\n");
    for (int i=0;i<G.n;i++)
    {
        for (int j=0;j<G.n;j++)
            printf("%d ",*(*(G.m+i)+j));
        printf("\n");
    }
    /// Orientat
    printf("\nAdjacency matrix(D):\n");
    for (int i=0;i<D.n;i++)
    {
        for (int j=0;j<D.n;j++)
            printf("%d ",*(*(D.m+i)+j));
        printf("\n");
    }
    int source;
    printf("\nSource = ");
    scanf("%d",&source);
    FILE* fout=fopen("matrix_file.txt","w");
    if (fout == NULL)
    {
        printf("Error\n");
        exit(2);
    }
    fprintf(fout,"For Graph -- ");BFS(G,source,fout);
    fprintf(fout,"\nFor Digraph -- ");BFS(D,source,fout);
    fclose(fout);
    return 0;
}
