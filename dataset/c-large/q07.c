// https://www.hackerrank.com/challenges/divisible-sum-pairs

#include <stdio.h>

int main()
{
    int n, k, ans = 0;
    scanf("%d %d", &n, &k);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if ((A[i] + A[j]) % k == 0)
                ans++;

    printf("%d\n", ans);

    return 0;
}