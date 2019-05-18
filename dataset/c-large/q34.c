// https://www.hackerrank.com/challenges/cut-the-sticks

#include <stdio.h>

int findMin(int n, int A[n]);
int main()
{
    int n, cuts;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    while (1)
    {
        int min = findMin(n, A), cuts = 0;

        for (int i = 0; i < n; i++)
            if (A[i] > 0)
            {
                A[i] -= min;
                cuts++;
            }

        if (cuts == 0)
            break;

        printf("%d\n", cuts);
    }

    return 0;
}

int findMin(int n, int A[n])
{
    int min = 1001;

    for (int i = 0; i < n; i++)
        if (A[i] < min && A[i] > 0)
            min = A[i];

    return min;
}