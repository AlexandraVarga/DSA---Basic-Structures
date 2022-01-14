#include <stdio.h>
#include <stdlib.h>

/*****************************************************
  Citirea datelor despre un graf dintr-un fisier
  cu reprezentarea grafului prin liste de adiacenta statice.
  In fisier se da numarul n de varfuri ale grafului,
  apoi muchiile sub forma de perechi i j, cu 0<=i,j<n
  (i si j reprezinta indicii varfurilor conectate prin
   arc (sau muchie)).
  Graful se parcurge BFS si se scriu într-un fisier
  nodurile în ordinea parcurgerii.
******************************************************/

typedef struct {
    int n;      // numar de varfuri
    int *t;     // tabloul de indici ai "inceputurilor" de liste (va fi alocat dinamic)
    int *liste; // tabloul ce va contine listele de adiacenta (va fi alocat dinamic)
} Graf;     // structura pentru memorarea grafului prin liste de adiacenta dinamice

enum { NEVIZITAT, VIZITAT };

/// TODO: de definit o structura Coada si
/// operatiile initializeaza, enqueue, dequeue, goala

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

void printErr() {
    printf("Memorie insuficienta!\n");
    exit(1);
}

void bfs( Graf G, int nodSursa, FILE* f)
{
	int* vizitate; /* pentru marcarea nodurilor vizitate */
	vizitate = calloc(G.n, sizeof(int));
	if (vizitate == NULL) printErr();

///	Coada Q; /* coada nodurilor - intregi */
    queue Q;
	int i, v, w; /* noduri */

///	initializeaza( Q );
    Q=createEmpty(Q);
	for ( i = 0; i < G.n; i++ ) /* marcam toate nodurile ca nevizitate */
		vizitate[ i ] = NEVIZITAT;
	vizitate[ nodSursa ] = VIZITAT; /* marcam nodul sursa ca vizitat */

	//procesam informatia pt nodSursa;
	Q=enqueue( nodSursa, Q );
	fprintf(f,"BFS(G,%d): %d ",nodSursa, nodSursa);
	// nodSursa va fi primul nod scos din coada
	while( ! isEmpty( Q ))
	{
		v = Q.head->key;
		Q = dequeue( Q );
		w = G.t[v];
		while ( G.liste[w] != -1 )
        {
            if ( vizitate[ G.liste[w] ] == NEVIZITAT )
			{
				vizitate[ G.liste[w] ] = VIZITAT;
				fprintf(f,"%d ",G.liste[w]);
				Q=enqueue( G.liste[w], Q );
			}
			w++;
        }
	}
}

void citesteGraf(FILE* f, Graf* pG) {
    fscanf(f, "%d", &pG->n);    // citeste nr. de varfuri

    // Alocam dinamic tabloul t, de dimensiune n:
    pG->t = calloc(pG->n, sizeof(int));
    if (pG->t == NULL) printErr();  // alocare esuata

    int i;
    for (i=0; i<pG->n; i++) {
        // initializam (liste vide)
        pG->t[i] = -1;  // t[i] ar contine indicele (in tabloul liste) de la care incepe lista de noduri adiacente cu i
    }

    // dimensiunea maxima a tabloului liste este n^2 (maxim n-1 varfuri adiacente cu
    // fiecare varf, plus sfarsitul fiecarei liste de adiacenta)
    pG->liste = calloc(pG->n * pG->n, sizeof(int));
    if (pG->liste == NULL) printErr();  // alocare esuata
    int v, w;

    for (int j=0;j<pG->n * pG->n;j++)
        pG->liste[j]=-1;
    pG->t[0]=0;
    int n = -1;
    int prev = 0;
    // citeste pe rand perechi (v, w) si memoreaza arcul/muchia in listele de adiacenta statice:
    while (fscanf(f, "%d%d", &v, &w) == 2) {
        /// TODO: memoreaza arcul/muchia in listele de adiacenta statice
        if (v != prev)
        {
            prev++;
            while (v != prev)
            {
                n++;
                pG->liste[n]=-1;
                prev++;
            }
            n++;
            pG->t[v]=n+1;
        }
        n++;
        pG->liste[n]=w;
    }
    while (v <= pG->n)
    {
        n++;
        pG->liste[n]=-1;
        v++;
    }
    /*
    Listele statice:
    for(int i=0;i<n;i++)
        printf("%d ",pG->liste[i]);
    printf("\n");
    for(int i=0;i<pG->n;i++)
        printf("%d ",pG->t[i]);
    printf("\n");
    */
}

int main()
{
    FILE* f1 = fopen("graf_neorientat.txt", "r");
    if (f1 == NULL) {
        perror("graf_neorientat.txt");
        exit(1);
    }
    Graf G;
    citesteGraf(f1, &G);
    fclose(f1);

    FILE* f2 = fopen("graf_orientat.txt","r");
    if (f2 == NULL)
    {
        perror("graf_orientat.txt");
        exit(3);
    }

    Graf D; /// condsider D graf orientat
    citesteGraf(f2, &D);
    fclose(f2);

    int v;
    printf("Numarul de noduri: %d. \nDati nodul sursa: ", G.n);
    scanf("%d", &v);

    FILE* fout = fopen("bfs.txt","w");
    if (fout == NULL) {
        perror("bfs.txt");
        exit(2);
    }

    fprintf(fout,"For graph -- ");bfs(G, v, fout);
    fprintf(fout,"\nFor digraph -- ");bfs(D,v,fout);
    fclose(fout);
    return 0;
}
