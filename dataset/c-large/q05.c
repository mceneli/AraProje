// https://www.hackerrank.com/challenges/breaking-best-and-worst-records

#include <stdio.h>

int main()
{
    int n, increase = 0, decrease = 0;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int max = A[0], min = max;

    for (int i = 1; i < n; i++)
    {
        if (A[i] > max)
        {
            max = A[i];
            increase++;
        }
        else if (A[i] < min)
        {
            min = A[i];
            decrease++;
        }
    }

    printf("%d %d\n", increase, decrease);

    return 0;
}