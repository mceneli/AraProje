// https://www.hackerrank.com/challenges/electronics-shop

#include <stdio.h>

int main()
{
    int s, n, m;
    scanf("%d %d %d", &s, &n, &m);
    int KEY[n], USB[m];

    for (int i = 0; i < n; i++)
        scanf("%d", &KEY[i]);

    for (int i = 0; i < m; i++)
        scanf("%d", &USB[i]);

    int sum, max = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum = KEY[i] + USB[j];

            if (sum > max && sum <= s)
                max = sum;
        }
    }

    if (max == 0)
        max = -1;

    printf("%d\n", max);

    return 0;
}