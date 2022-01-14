#include <stdio.h>
#include <stdlib.h>

void merge(int* a, int low, int mid, int high)
{
    int* aux = (int*)malloc((high-low+1)*sizeof(int));
    int i = low;
    int k = low;
    int j = mid + 1;
    while (i <= mid && j <= high)
        if (a[i] <= a[j])
        {
            aux[k++] = a[i];
            i++;
        }
        else
        {
            aux[k++] = a[j];
            j++;
        }
    while (i <= mid)
        aux[k++] = a[i++];
    while (j <= high)
        aux[k++] = a[j++];
    for (int p = low; p <= high; p++)
        a[p] = aux[p];
}

void mergeSort(int* a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high)/2;
        mergeSort(a, low, mid);
        mergeSort(a, mid+1, high);
        merge(a, low, mid, high);
    }
}

void printArray(int* a, int n)
{
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int v[] = {9, 3, 12, 5, 7, 2, 9, 5};
    int n = sizeof(v)/sizeof(int);
    printf("\nn = %d\n", n);
    printArray(v, n);
    mergeSort(v, 0, n-1);
    printArray(v, n);
    return 0;
}
