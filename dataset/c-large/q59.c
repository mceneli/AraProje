// https://www.hackerrank.com/challenges/absolute-permutation/problem

#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, k, j = 0, p = 1;
        scanf("%d %d", &n, &k);
    
        if (k == 0)
            for (int i = 0; i < n; i++)
                printf("%d ", i+1);
        else if (k <= n/2 && n % k == 0 && (n/k) % 2 == 0)
            while (j < n)
            {
                for (int i = 0; i < k; i++, j++)
                    printf("%d ", j+(k*p)+1);

                p *= -1;
            }
        else
            printf("-1");

        printf("\n");
    }

    return 0;
}