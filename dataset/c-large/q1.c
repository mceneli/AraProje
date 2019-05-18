/*
    https://www.hackerrank.com/contests/projecteuler/challenges/euler001
*/

#include <stdio.h>

int main()
{
    int q;
    scanf("%d", &q);
    
    while (q--)
    {
        long n, sum;
        scanf("%ld", &n);
        n--;
        sum = 3*(((n/3)*(n/3+1))/2) + 5*(((n/5)*(n/5+1))/2) - 15*(((n/15)*(n/15+1))/2);
        printf("%ld\n", sum);
    }

    return 0;
}