#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
    int val;
    int status;
} Cell;

enum { FREE, OCCUPIED };

void afisare(Cell *T, int m)
{
    int i;
    printf("\n\nTabela de dispersie este \n");
    for (i = 0; i < m; i++)
    {
        if(T[i].status == OCCUPIED)
            printf("T[%d]=%d\n",i,T[i]);
        else
            printf("T[%d]= --\n",i);

    }
}

///verificam daca toata tabela e ocupata
int hash_table_occupied(Cell *T, int m)
{
    int i;
    for (i = 0; i < m; i++)
        if (T[i].status == FREE)
            return 0;
    return 1;
}

void insert_linear_probing(int k, Cell *T, int m)
{

    if (hash_table_occupied(T, m))
    {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }
    int i = 0;
    int collision = 1;
    int h = 0;
    do
    {
        h = linear_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
            i++;
    }
    while (collision);
    T[h].status = OCCUPIED;
    T[h].val = k;
}


int h_prime(int k, int m)
{
    return k % m;
}

///returneaza pozitia la care se va verifica tabela de dispersie folosind verificarea liniara
int linear_probing(int k, int m, int i)
{
    ///h(k, i) = (h’(k)+i) mod m
    int val = (h_prime(k,m) + i ) % m;
    return val;
}

int quadratic_probing(int k, int m, int i)
{
    int c1,c2=c1=1;
    int val= (h_prime(k,m)+c1*i+c2*i*i)%m;
    return val;
}

void insert_quadratic_probing(int k, Cell *T, int m)
{
    if (hash_table_occupied(T, m))
    {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }
    int i = 0;
    int collision = 1;
    int h = 0;
    do
    {
        h = quadratic_probing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
            i++;
    }
    while (collision);
    T[h].status = OCCUPIED;
    T[h].val = k;

}

int h_prime2(int k, int m)
{
    return (5-k%m);
}

int double_hashing(int k, int m, int i)
{
    int val= ((h_prime(k,m)+i*h_prime2(k,m))%m);
    return val;
}
void insert_double_hashing(int k, Cell *T, int m)
{
    if (hash_table_occupied(T, m))
    {
        printf("Nu se mai poate insera cheia %d, tabela este plina \n", k);
        return;
    }
    int i = 0;
    int collision = 1;
    int h = 0;
    do
    {
        h = double_hashing(k, m, i);
        if (T[h].status == FREE)
            collision = 0;
        else
            i++;
    }
    while (collision);
    T[h].status = OCCUPIED;
    T[h].val = k;
}


void set_table_free(Cell *T, int m)
{
    ///initializam tabela
    int i;
    for (i = 0; i<m; i++)
        T[i].status = FREE;
}

int main()
{
    int m = 7;
    Cell *T = (Cell*) malloc(m*sizeof(Cell)); ///tabela de dispersie - se aloca

    set_table_free(T, m);
    afisare(T, m);
    insert_linear_probing(19, T, m);
    insert_linear_probing(36, T, m);
    insert_linear_probing(5, T, m);
    insert_linear_probing(21, T, m);
    insert_linear_probing(4, T, m);
    insert_linear_probing(26, T, m);
    insert_linear_probing(14, T, m);
    insert_linear_probing(17, T, m);
    afisare(T, m);

    ///resetam tabela
    set_table_free(T, m);
    afisare(T, m);
    insert_quadratic_probing(19, T, m);
    insert_quadratic_probing(36, T, m);
    insert_quadratic_probing(5, T, m);
    insert_quadratic_probing(21, T, m);
    insert_quadratic_probing(4, T, m);
    insert_quadratic_probing(26, T, m);
    insert_quadratic_probing(14, T, m);
    insert_quadratic_probing(17, T, m);
    afisare(T, m);

    set_table_free(T, m);
    afisare(T, m);
    insert_double_hashing(19, T, m);
    insert_double_hashing(36, T, m);
    insert_double_hashing(5, T, m);
    insert_double_hashing(21, T, m);
    insert_double_hashing(4, T, m);
    insert_double_hashing(26, T, m);
    insert_double_hashing(14, T, m);
    insert_double_hashing(17, T, m);
    afisare(T, m);

    free(T);
    return 0;
}
