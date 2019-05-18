// https://www.hackerrank.com/challenges/minimum-distances

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, diff;
    scanf("%d", &n);
    int *A = malloc(n*sizeof(int));
    int min = n;

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (A[i] == A[j])
            {
                diff = j-i;

                if (diff < min)
                    min = diff;
            }

    if (min == n)
        min = -1;

    printf("%d\n", min);
    free(A);

    return 0;
}