///permutari
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
int n;
int vect[MAXSIZE];

void afisare(int k,int gasit)
{
    int i;

    for(i=1; i<=k; i++)
    {
        printf("%d ",vect[i]);
    }
    if(k==n && gasit==0)
    {
        printf(" -solution");
    }

    printf("\n");

}

int valid(int k)
{
    int i;
    for(i=1; i<k; i++)
    {
        if(vect[k]==vect[i])
            return 0;
    }

    return 1;
}

void permutari(int k)
{
    int i;
    int gasit=0;
    for(i=1; i<=n; i++)
    {
        vect[k]=i;

        if(valid(k))
        {
            if(k<n)
            {
                gasit=0;
                afisare(k,gasit);
                permutari(k+1);
            }
            else
            {
                gasit=0;
                afisare(k,gasit);
            }
        }
        else
        {
            gasit=1;
            afisare(k,gasit);
        }

    }


}

int main()
{

    printf("Introduceti numarul de elemente:");
    scanf("%d",&n);
    printf("\nPermutarile de %d elemente sunt:\n",n);
    permutari(1);

    return 0;
}
