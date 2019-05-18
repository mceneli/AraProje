// https://www.hackerrank.com/challenges/migratory-birds

#include <stdio.h>

int main()
{
    int n, size, max_type, max;
    scanf("%d", &n);
    int A[n], Types[6] = {0};

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        Types[A[i]]++;
    }

    max = Types[1];

    for (int i = 2; i <= 5; i++)
        if (Types[i] > max)
        {
            max = Types[i];
            max_type = i;
        }

    printf("%d\n", max_type);

    return 0;
}