// https://www.hackerrank.com/challenges/fair-rations

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k = 0, ans = 0;
    scanf("%d", &n);
    int *B = malloc(n*sizeof(int));
    int *Odds = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &B[i]);

        if (B[i] % 2 == 1)
        {
            Odds[k] = i;
            k++;
        }
    }

    if (k % 2 != 0)
        printf("NO\n");
    else
    {
        for (int i = 0; i < k-1; i+= 2)
            ans += Odds[i+1]-Odds[i];

        printf("%d\n", ans*2);
    }

    return 0;
}