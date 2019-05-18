// https://www.hackerrank.com/challenges/kaprekar-numbers

#include <stdio.h>

int isKaprekar(long x);
int main()
{
    int p, q, j = 0, A[100];
    scanf("%d %d", &p, &q);

    for (long i = p; i <= q; i++)
        if (isKaprekar(i) == 1)
        {
            A[j] = i;
            j++;
        }

    if (j == 0)
        printf("INVALID RANGE\n");
    else
        for (int i = 0; i < j; i++)
            printf("%d ", A[i]);

    return 0;
}

int isKaprekar(long x)
{
    long sqr = x*x, temp = sqr;
    int digit = 0, j = 0, k = 1, sum1 = 0, sum2 = 0;

    while (temp > 0)
    {
        digit++;
        temp /= 10;
    }

    while (j < (digit-(digit/2)))
    {
        sum1 += (sqr % 10)*k;
        sqr /= 10;
        k *= 10;
        j++;
    }

    k = 1;

    while (j < digit)
    {
        sum2 += (sqr % 10)*k;
        sqr /= 10;
        k *= 10;
        j++;
    }

    if (sum1 + sum2 == x)
        return 1;
    else
        return 0;
}