// https://www.hackerrank.com/challenges/circular-array-rotation

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    int *A = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < q; i++)
    {
        int m;
        scanf("%d", &m);
        printf("%d\n", A[((m+n) - (k % n)) % n]);
    }
    
    free(A);
    return 0;
}