// https://www.hackerrank.com/challenges/equality-in-a-array

#include <stdio.h>

int frequance(int n, int A[n], int x);
int main()
{
    int n,temp, max = 0;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
    {
        temp = frequance(n, A, A[i]);

        if (temp > max)
            max = temp;
    }

    printf("%d\n", n-max);

    return 0;
}

int frequance(int n, int A[n], int x)
{
    int ans = 0;

    for (int i = 0; i < n; i++)
        if (A[i] == x)
            ans++;

    return ans;
}