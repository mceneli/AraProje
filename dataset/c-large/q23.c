// https://www.hackerrank.com/challenges/beautiful-days-at-the-movies

#include <stdio.h>
#include <math.h>

int reversed(int x);
int main()
{
    int x, y, k, beauty = 0;
    float temp;
    scanf("%d %d %d", &x, &y, &k);

    for (int i = x; i <= y; i++)
    {
        temp = (float)((i - reversed(i))) / (float)k;
        if (temp == roundf(temp))
            beauty++;
    }

    printf("%d\n", beauty);

    return 0;
}

int reversed(int x)
{
    int ans = 0, j = 0, k = 1, A[10];

    while (x > 0)
    {
       A[j] = x % 10;
       x /= 10;
       j++;
    }

    for (int i = j-1; i >= 0; i--)
    {
        ans += k * A[i];
        k *= 10;
    }

    return ans;
}