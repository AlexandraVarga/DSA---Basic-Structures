#include <stdio.h>
#include <limits.h>
#define MAX 1000

int s,n, monede[MAX], Min[MAX + 1];
void read();
void DP();
void write();
int main()
{
    read();
    DP();
    write();
	return 0;
}
void read()
{
    int i;
    scanf("%d",&n);
    scanf("%d",&s);
    for(i = 0; i < n; i++)
        scanf("%d",&monede[i]);
}
void DP()
{
    for (int i = 0; i <= s; i++)
        Min[i] = INT_MAX;
    Min[0] = 0;
    for (int i = 1; i <= s; i++)
        for (int j = 0; j < n; j++)
            if (monede[j] <= i && Min[i-monede[j]] + 1 < Min[i])
                Min[i] = Min[i-monede[j]]+1;
}
void write()
{
    printf("%d \n", Min[s]);
    for(int i = 0; i <= s; i++)
        printf("%d ", Min[i]);
}
