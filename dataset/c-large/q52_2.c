// https://www.hackerrank.com/challenges/flatland-space-stations

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, x, ans = 0;
    scanf("%d %d", &n, &m);
    int *A = malloc(n*sizeof(int));
    int min = n, max = 0;

    for (int i = 0; i < n; i++)
        A[i] = 0;
    
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &x);
        A[x]++;

        if (x < min)
            min = x;
        if (x > max)
            max = x;
    }

    int temp = min;

    for (int i = min+1; i <= max; i++)
        if (A[i] == 1)
        {
            if (i-temp > ans)
                ans = i-temp;
            
            temp = i;
        }
    
    ans /= 2;

    if (n-1-max > ans)
        ans = n-1-max;
    if (min > ans)
        ans = min;

    printf("%d\n", ans);

    free(A);
    return 0;
}