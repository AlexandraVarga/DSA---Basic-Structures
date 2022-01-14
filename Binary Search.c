#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* a, int low, int high, int x)
{
    if (low == high)
        return low;
    int mid = (low + high)/2;
    if (x <= a[mid])
        return binarySearch(a, low, mid, x);
    else
        return binarySearch(a, mid+1, high, x);
}

int main()
{
    int a[] = {2, 3, 5, 7, 8, 11, 20};
    int n = sizeof(a)/sizeof(int);
    int to_find[] = {1, 2, 3, 4, 5, 6, 21};
    int m = sizeof(to_find)/sizeof(int);
    for (int i = 0; i < m; i++)
        printf("\nbinarySearch(a,0,%d,%d) = %d\n", n-1, to_find[i], binarySearch(a, 0, n-1, to_find[i]));
    return 0;
}
