// https://www.hackerrank.com/challenges/grading

#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
        if (A[i] >= 38 && A[i] % 5 >= 3)
                A[i] += 5 - (A[i] % 5);

    for (int i = 0; i < n; i++)
        printf("%d\n", A[i]);

    return 0;
}