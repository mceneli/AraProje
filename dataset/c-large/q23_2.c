// https://www.hackerrank.com/challenges/beautiful-days-at-the-movies

#include <stdio.h>
#include <math.h>

int reversed(int x);
int main()
{
    int x, y, k, beauty = 0;
    scanf("%d %d %d", &x, &y, &k);

    for (int i = x; i <= y; i++)
        if ((i - reversed(i)) % k == 0)
            beauty++;

    printf("%d\n", beauty);

    return 0;
}

int reversed(int x)
{
    int ans = 0;

    while (x > 0)
    {
       ans = ans*10 + (x % 10);
       x /= 10;
    }

    return ans;
}