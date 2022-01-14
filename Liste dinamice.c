#include <stdio.h>
#include <stdlib.h>

/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin liste de adiacenta dinamice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge BFS si se scriu într-un fisier
  nodurile în ordinea parcurgerii.
******************************************************/

typedef struct nod {
    int v;
    struct nod* next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT* *t;    // tabloul de liste (va fi alocat dinamic)
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

enum { NEVIZITAT, VIZITAT };

/// TODO: de definit o structura Coada si
/// operatiile initializeaza, enqueue, dequeue, goala

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
    newNode->v=key;
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
        printf("%d ",p->v);
        p=p->next;
    }
    printf("\n");
}

void printErr() {
    printf("Memorie insuficienta!\n");
    exit(1);
}

void BFS( Graf G, int nodSursa, FILE* f )
{
	int* vizitate; /* pentru marcarea nodurilor vizitate */
	vizitate = calloc(G.n, sizeof(int));
	if (vizitate == NULL) printErr();

    queue Q = createEmpty(Q);

	int i; /* noduri */


	for ( i = 0; i < G.n; i++ ) /* marcam toate nodurile ca nevizitate */
		vizitate[ i ] = NEVIZITAT;
	vizitate[ nodSursa ] = VIZITAT; /* marcam nodul sursa ca vizitat */

	Q=enqueue( nodSursa, Q );

	fprintf(f,"BFS(G,%d): %d ",nodSursa, nodSursa);
	// nodSursa va fi primul nod scos din coada
	while( ! isEmpty( Q ))
	{
		int v = Q.head->v;
		Q = dequeue( Q );
		NodeT* w = G.t[v];
		while (w != NULL)
		{

			if ( vizitate[ w->v ] == NEVIZITAT )
			{
				vizitate[ w->v ] = VIZITAT;
				fprintf(f,"%d ",w->v);
				Q=enqueue( w->v, Q );
			}
			w=w->next;
		}
	}
	printf("\n");
}

void citesteGrafOrientat(FILE* f, Graf* pG) {
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic tabloul de liste de adiacenta de dimensiune n:
    pG->t = calloc(pG->n, sizeof(NodeT*));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i=0; i<pG->n; i++) {
        // initializam (liste vide)
        pG->t[i] = NULL;
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in listele de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        /// TODO: memoreaza arcul/muchia in listele de adiacenta
        NodeT* p=(NodeT*)malloc(sizeof(NodeT));
        p->next=NULL;
        p->v=w;
        if (pG->t[v] == NULL)
            pG->t[v]=p;
        else
        {
            p->next=pG->t[v];
            pG->t[v]=p;
        }

    }
}

void citesteGrafNeorientat(FILE* f, Graf* pG) {
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic tabloul de liste de adiacenta de dimensiune n:
    pG->t = calloc(pG->n, sizeof(NodeT*));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i=0; i<pG->n; i++) {
        // initializam (liste vide)
        pG->t[i] = NULL;
    }

    int v, w;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in listele de adiacenta:
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        /// TODO: memoreaza arcul/muchia in listele de adiacenta
        NodeT* p=(NodeT*)malloc(sizeof(NodeT));
        p->next=NULL;
        p->v=w;
        if (pG->t[v] == NULL)
            pG->t[v]=p;
        else
        {
            p->next=pG->t[v];
            pG->t[v]=p;
        }
        NodeT* q=(NodeT*)malloc(sizeof(NodeT));
        q->next=NULL;
        q->v=v;
        if (pG->t[w] == NULL)
            pG->t[w]=q;
        else
        {
            q->next=pG->t[w];
            pG->t[w]=q;
        }

    }
}

void printList(NodeT* first)
{
    NodeT* p=first;
    while (p != NULL)
    {
        printf("%d ",p->v);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    FILE* f = fopen("graf.txt", "r");
    if (f == NULL) {
        perror("graf.txt");
        exit(1);
    }
    Graf G;
    citesteGrafNeorientat(f, &G);
    fclose(f);

    f = fopen("graf.txt", "r");
    if (f == NULL) {
        perror("graf.txt");
        exit(1);
    }

    Graf D;
    citesteGrafOrientat(f,&D);
    fclose(f);

    for (int i=0;i<G.n;i++)
    {
        printf("L(%d): ",i);
        printList(G.t[i]);
    }

    int v;
    printf("Numarul de noduri = %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    FILE* fout = fopen("bfs.txt","w");
    if (fout == NULL)
    {
        perror("bfs.txt");
        exit(1);
    }

    fprintf(fout,"For Graph -- ");BFS(G, v, fout);
    fprintf(fout,"\n");
    fprintf(fout,"For Digraph -- ");BFS(D, v, fout);
    fclose(fout);
    return 0;
}
