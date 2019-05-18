// https://www.hackerrank.com/challenges/the-hurdle-race

#include <stdio.h>

int findMax(int n, int A[n]);
int main()
{
    int n, k, max, magic;
    scanf("%d %d",&n,&k);
    int H[n];

    for(int i = 0; i < n; i++)
       scanf("%d",&H[i]);
    
    max = findMax(n, H);
    magic = max - k;

    if (magic < 0)
        magic = 0;

    printf("%d\n", magic);

    return 0;
}

int findMax(int n, int A[n])
{
    int max = A[0];

    for (int i = 1; i < n; i++)
        if (A[i] > max)
            max = A[i];

    return max;
}