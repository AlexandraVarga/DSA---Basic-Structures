///regine
#include <stdio.h>
#include <stdlib.h>
#define MAXN 10
int x[ MAXN ]; /* solution vector */
int n; /* chessboard size */
int solNb;  /* solution number */
enum { FALSE, TRUE };

int phi( int k )
/* check the continuation conditions - the k-th queen threatens none of the queens: 1, 2, ..., k-1 */
{
    int i;
    for(i=1; i<k; i++)
    {
        if(x[i]==x[k])
            return 0;
        else if(abs(k-i)==abs(x[k]-x[i]))
            return 0;
    }
    return 1;
}

void displaySolution()
/* display the chessboard configuration */
{
    int i,j;
    char t[10][10]= {0};
    for( i=1; i<=n; i++)
        t[i][x[i]]=1;
    for( i=1; i<=n; i++)
    {
        for( j=1; j<=n; j++)
            if(t[i][j]==0)
                printf(".");
            else
                printf("r");

        printf("\n");
    }
    solNb++;
    printf( "\nSolution %d:\n", solNb );
    /// TODO
}

void recQueens( int k )
/* find all possible arrangements of n queens on a chessboard such that no queen
   threatens another */
{
    int j;
    for ( j = 1; j <= n; j++ )
    {
        x[ k ] = j;
        if ( phi( k ) )
        {
            if ( k < n )
                recQueens( k + 1 );
            else
                displaySolution();
        }
    }
}
int main()
{
    printf( "\nNumber of queens=" );
    scanf( "%d", &n );
    solNb = 0;
    recQueens( 1 );
    printf( "\nEnd." );
    return 0;
}
