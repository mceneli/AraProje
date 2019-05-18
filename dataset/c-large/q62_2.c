// // https://www.hackerrank.com/challenges/larrys-array

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSortable(int n, int A[]);
int main()
{
    int q;
    scanf("%d", &q);

    while (q--)
    {
        int n;
        scanf("%d", &n);
        int *A = malloc(n*sizeof(int));

        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);

        printf((isSortable(n, A)) ? "YES\n" : "NO\n");
    }

    return 0;
}

bool isSortable(int n, int A[])
{
    int count = 0;

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (A[i] > A[j])
                count++;

    return ((count % 2 == 0) ? 1 : 0);
}