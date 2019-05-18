// https://www.hackerrank.com/challenges/manasa-and-stones

#include <stdio.h>

int main()
{
    int t, n, a, b;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d %d %d", &n, &a, &b);

        if (a > b)
            for (int i = 0; i < n; i++)
                printf("%d ", (n-1-i)*b + i*a);
        else if (b > a)
            for (int i = 0; i < n; i++)
                printf("%d ", (n-1-i)*a + i*b);
        else
            printf("%d", (n-1)*a);

        printf("\n");
    }

    return 0;
}