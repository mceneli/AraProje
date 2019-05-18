/*
    https://www.hackerrank.com/challenges/larrys-array
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t, n, temp;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);
        int *A = malloc(n*sizeof(int));
        int flag, temp = n;

        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);

        while (temp--)
        {
            flag = 0;

            for (int i = 1; i < n-1; i++)
            {
                if (A[i] > A[i-1] && A[i] > A[i+1] && A[i-1] > A[i+1])
                {
                    temp = A[i-1];
                    A[i-1] = A[i+1];
                    A[i+1] = A[i];
                    A[i] = temp;
                }
                else if (A[i] < A[i-1] && A[i] < A[i+1] && A[i-1] > A[i+1])
                {
                    temp = A[i+1];
                    A[i+1] = A[i-1];
                    A[i-1] = A[i];
                    A[i] = temp;
                }      
                else if (A[i+1] > A[i] && A[i] > A[i-1])
                    flag++;
            }

            if (flag == n-2)
                break;
        }

        if (flag == n-2)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}