// https://www.hackerrank.com/challenges/chocolate-feast

#include <stdio.h>

int main()
{
    int t, n, c, m, ans, temp;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d %d %d", &n, &c, &m);
        ans = n/c;
        temp = ans;

        while (temp >= m)
        {
            ans += temp/m;
            temp = temp/m + temp%m;
        }

        printf("%d\n", ans);
    }

    return 0;
}