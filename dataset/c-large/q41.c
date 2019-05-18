// https://www.hackerrank.com/challenges/taum-and-bday

#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        long ans, b, w, x, y, z;
        scanf("%ld %ld %ld %ld %ld", &b, &w, &x, &y, &z);

        if (x > y+z)
            ans = (b+w)*y + b*z;
        else if (y > x+z)
            ans = (b+w)*x + w*z;
        else
            ans = b*x + w*y;

        printf("%ld\n", ans);
    }

    return 0;
}