// https://www.hackerrank.com/challenges/drawing-book

#include <stdio.h>

int solve(int n, int p);
int main() 
{
    int n, p; 
    scanf("%d %d", &n, &p);

    int result = solve(n, p);
    printf("%d\n", result);

    return 0;
}

int solve(int n, int p)
{
    if (n/2 >= p)
        return p/2;
    else
        return n/2 - p/2;
}