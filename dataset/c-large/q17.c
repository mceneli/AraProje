// https://www.hackerrank.com/challenges/picking-numbers

#include <stdio.h>

int main()
{
    int n, diff1, diff2, max = 0;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    
    for (int i = 0; i < n; i++)
    {
        diff1 = 0, diff2 = 0;

        for (int j = 0; j < n; j++)
        {
            if (A[i] - A[j] == 1)
                diff1++;
            else if (A[j] - A[i] == -1)
                diff2++;
            else if (A[i] == A[j])
            {
                diff1++;
                diff2++;
            }
        }

        if (diff1 > max)
            max = diff1;  

        if (diff2 > max)
            max = diff2;
    }
    
    printf("%d\n", max);

    return 0;
}