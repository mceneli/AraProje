// https://www.hackerrank.com/challenges/apple-and-orange

#include <stdio.h>

int main()
{
    int a, b, s, t, m, n, eat1 = 0, eat2 = 0;

    scanf("%d %d", &s, &t);
    scanf("%d %d", &a, &b);
    scanf("%d %d", &m, &n);

    int apples[m], oranges[n];

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &apples[i]);
        if (s - (a + apples[i]) <= 0 && t - (a + apples[i]) >= 0)
            eat1++;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &oranges[i]);
        if (t - (b + oranges[i]) >= 0 && (b + oranges[i]) - s >= 0)
            eat2++;
    }

    printf("%d\n%d\n", eat1, eat2);

    return 0;
}