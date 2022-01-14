///combinari
#include<stdio.h>
int x[100];

int phi(int k)
{
    int i;
    for(i=0; i<k; i++)
        if(x[k]<x[i] || x[k]==x[i])
            return 0;
    return 1;
}

void list(int x[], int n)
{
    int i;
    for( i=0; i<n; i++)
        printf(" %d",x[i]);
    printf("   e solutie");
    printf("\n");
}

void bk(int k,int n,int m)
{
    int i;
    for(i=1; i<=n; i++)
    {
        x[k]=i;
        if(phi(k))
            if(k<m-1)
                bk(k+1,n,m);
            else
                list(x,m);
    }
}

int main()
{
    int n,m;
    printf("n=");
    scanf("%d", &n);
    printf("m=");
    scanf("%d",&m);
    bk(0,n,m);
    return 0;
}
