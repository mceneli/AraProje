// https://www.hackerrank.com/challenges/non-divisible-subset/problem

#include <stdio.h>
#include <math.h>

int main()
{
    int n, k, x, ans = 0, Mod[101] = {0};
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        Mod[x % k]++;
    }

    if (k % 2 == 0 && Mod[k/2] != 0)
        ans++;
    if (Mod[0] != 0)
        ans++;

    for (int i = 1; i < ceil((float)k/2.0); i++)
    {
        if (Mod[i] > Mod[k-i])
            ans += Mod[i];
        else
            ans += Mod[k-i];
    }

    printf("%d\n", ans);

    return 0;
}