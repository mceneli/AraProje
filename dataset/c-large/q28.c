// https://www.hackerrank.com/challenges/jumping-on-the-clouds-revisited

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k, j = 0, score = 100;
    scanf("%d %d", &n, &k);
    int *A = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    do
    {
        if (A[(j+k) % n] == 0)
            score -= 1;
        else
            score -= 3;

        j += k;
    }
    while (j % n != 0);

    printf("%d\n", score);

    free(A);
    return 0;
}