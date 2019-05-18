// https://www.hackerrank.com/challenges/counting-valleys

#include <stdio.h>

int main()
{
    int n, sum = 0, valleys = 0;
    scanf("%d", &n);
    char A[n];

    for (int i = 0; i < n; i++)
        scanf(" %c", &A[i]);

    for (int i = 0; i < n; i++)
    {
        if (A[i] == 'U')
            sum++;
        else
            sum--;

        if (A[i] == 'U' && sum == 0)
            valleys++;
    }

    printf("%d\n", valleys);

    return 0;
}