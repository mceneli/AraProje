/*
    https://www.hackerrank.com/contests/projecteuler/challenges/euler002
*/

#include <stdio.h>
#define edge 40000000000000000

int main()
{
    int t, j = 0;
    long A[100], n, a = 1, b = 2, c, sum;
    scanf("%d", &t);

    while (b < edge)
    {
        A[j] = b;
        j++;

        for (int i = 0; i < 3; i++)
        {
            c = a+b;
            a = b;
            b = c;
        }
    }

    while (t--)
    {
        sum = 0;
        scanf("%ld", &n);
        
        for (int i = 0; i < j; i++)
        {
            if (A[i] <= n)
                sum += A[i];
            else
                break;
        }

        printf("%ld\n", sum);
    }

    return 0;
}