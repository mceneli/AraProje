// https://www.hackerrank.com/challenges/between-two-sets

#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int A[n], B[m];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    
    for (int i = 0; i < m; i++)
        scanf("%d", &B[i]);

    int max_A = A[0], min_B = B[0];

    for (int i = 0; i < n; i++)
        if (A[i] > max_A)
            max_A = A[i];

    for (int i = 0; i < m; i++)
        if (B[i] < min_B)
            min_B = B[i];

    int k = max_A, tmp = k, flag = 0, factors = 0;
    
    while (k <= min_B)
    {
        for (int j = 0; j < n; j++)
        {
            if (k % A[j] != 0)
            {
                flag++;
                break;
            }
        }

        for (int j = 0; j < m; j++)
        {
            if (B[j] % k != 0)
            {
                flag++;
                break;
            }
        }

        if (flag == 0)
            factors++;
        
        k += tmp;
        flag = 0;
    }

    printf("%d\n", factors);

    return 0;
}