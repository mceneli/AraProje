// https://www.hackerrank.com/challenges/service-lane

#include <stdio.h>

int main()
{
    int n, t, i, j, min;
    scanf("%d %d", &n, &t);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    while (t--)
    {
        scanf("%d %d", &i, &j);
        min = 4;

        for (int p = i; p <= j; p++)
            if (A[p] < min)
            {
                min = A[p];

                if (min == 1)
                    break;
            }

        printf("%d\n", min);
    }

    return 0;
}