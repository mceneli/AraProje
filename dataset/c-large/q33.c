// https://www.hackerrank.com/challenges/library-fine

#include <stdio.h>

int main()
{
    int d1, m1, y1, d2, m2, y2, fine = 0;
    scanf("%d %d %d %d %d %d", &d1, &m1, &y1, &d2, &m2, &y2);

    if (y1 == y2)
    {
        if (m1 == m2)
        {
            if (d1 > d2)
                fine = 15*(d1-d2);
        }
        else if (m1 > m2)
            fine = 500*(m1-m2);
    }
    else if (y1 > y2)
        fine = 10000;

    printf("%d\n", fine);

    return 0;
}