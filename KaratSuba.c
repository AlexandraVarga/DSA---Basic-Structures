#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int size(int n)
{
    if (n == 0)
        return 1;
    int length = 0;
    while (n > 0)
    {
        length++;
        n = n/10;
    }
    return length;
}

int Karatsuba(int x, int y)
{
    if (x < 10 || y < 10)
        return x*y;
    int m = max(size(x), size(y))/2;
    int M = pow(10, m);
    int x1 = x/M;
    int x0 = x%M;
    int y1 = y/M;
    int y0 = y%M;
    int z0 = Karatsuba(x0, y0);
    int z2 = Karatsuba(x1, y1);
    int z1 = Karatsuba(x1+x0, y1+y0)-z2-z0;
    return z2*pow(10,2*m)+z1*pow(10, m)+z0;

}

int main()
{
    printf("Karatsuba(%d, %d) = %d", 15, 23, Karatsuba(15, 23));
    return 0;
}
