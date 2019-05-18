// https://www.hackerrank.com/challenges/sock-merchant

#include <stdio.h>

int main()
{
    int n, k, socks = 0;
    scanf("%d", &n);
    int A[n], B[101] = {0};

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
    {
        if (B[A[i]] == 0)
        {
            k = 1;

            for (int j = i+1; j < n; j++)
                if (A[i] == A[j])
                    k++;
                    
            socks += k/2;
            B[A[i]]++;
        }
    }

    printf("%d\n", socks);

    return 0;
}