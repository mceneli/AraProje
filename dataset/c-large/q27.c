// https://www.hackerrank.com/challenges/permutation-equation

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int *P = malloc((n+1)*sizeof(int));

    for (int i = 1; i <= n; i++)
        scanf("%d", &P[i]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (P[P[j]] == i)
            {  
                printf("%d\n", j);
                break;
            }
    
    free(P);
    return 0;
}