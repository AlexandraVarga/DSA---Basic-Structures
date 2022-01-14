#include <stdio.h>
#define MAX 1000

int s,n, monede[MAX], combinatii[MAX + 1];
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
    printf("Numarul de monede disponibile = ");
    scanf("%d",&n);
    printf("Suma = ");
    scanf("%d",&s);
    for(i = 0; i < n; i++)
        scanf("%d",&monede[i]);
}
void DP()
{
    combinatii[0] =  1;
    for (int mon = 0; mon < n; mon++)
        for (int i = monede[mon]; i <= s; i++)
            combinatii[i] += combinatii[i-monede[mon]];
}
void write()
{
    printf("%d \n", combinatii[s]);
    for(int i = 0; i <= s; i++)
        printf("%d ", combinatii[i]);
}
