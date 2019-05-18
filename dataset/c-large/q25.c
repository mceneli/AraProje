// https://www.hackerrank.com/challenges/save-the-prisoner

#include <stdio.h>

int main()
{
    int t, n, m, s;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        scanf("%d %d %d", &n, &m, &s);
        printf("%d\n", (m + s - 2) % n + 1);
    }

    return 0;
}