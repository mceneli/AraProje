// https://www.hackerrank.com/challenges/larrys-array

#include <stdio.h>
#include <stdlib.h>

int swapsInsertionSort(int n, int A[]);
int main()
{
    int t, n;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);
        int *A = malloc(n*sizeof(int));

        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);

        int k = swapsInsertionSort(n, A);

        printf((k % 2 == 0) ? "YES\n" : "NO\n");
    }

    return 0;
}

int swapsInsertionSort(int n, int A[])
{
    int swaps = 0;

    for (int i = 1; i < n; i++)
    {
        int key = A[i], j = i-1;

        while (j >= 0 && A[j] > key)
        {
            A[j+1] = A[j];
            swaps++, j--;
        }

        A[j+1] = key;
    }

    return swaps;
}