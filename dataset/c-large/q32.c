// https://www.hackerrank.com/challenges/sherlock-and-squares

#include <stdio.h>
#include <math.h>

int main()
{
    int q, squares;
    double x1, x2;
    scanf("%d", &q);

    while (q--)
    {
        scanf("%lf %lf", &x1, &x2);
        squares = floor(sqrt(x2)) - ceil(sqrt(x1)) + 1;
        printf("%d\n", squares);
    }

    return 0;
}