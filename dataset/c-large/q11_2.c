// https://www.hackerrank.com/challenges/sock-merchant

#include <stdio.h>

int main()
{
    int n, socks = 0;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
            if (A[i] == A[j] && A[i] != 0)
            {
                A[i] = 0;
                A[j] = 0;
                socks++;
            }
    }

    printf("%d\n", socks);

    return 0;
}