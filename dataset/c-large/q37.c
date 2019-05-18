// https://www.hackerrank.com/challenges/jumping-on-the-clouds

#include <stdio.h>

int main()
{
    int n, j = 0, steps = 0;
    scanf("%d", &n);
    int C[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &C[i]);

    while (j < n-1)
    {
        if (C[j+2] != 1)
            j += 2;
        else
            j++;

        steps++;
    }

    printf("%d\n", steps);

    return 0;
}