// https://www.hackerrank.com/challenges/strange-code

#include <stdio.h>
#include <math.h>

int main()
{
    double t;
    long col, ans;
    scanf("%lf", &t);

    col = ceil(log10((t+3)/3)/log10(2));
    ans = (pow(2, col)*3-3)-t+1;

    printf("%ld\n", ans);

    return 0;
}