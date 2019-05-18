// https://www.hackerrank.com/challenges/cats-and-a-mouse

#include <stdio.h>

int abs(int x);
int main()
{
    int q, x, y, z;
    scanf("%d", &q);
    char *A[q];

    for (int i = 0; i < q; i++)
    {
        scanf("%d %d %d", &x, &y, &z);

        if (abs(x-z) > abs(y-z))
            A[i] = "Cat B";
        else if (abs(x-z) < abs(y-z))
            A[i] = "Cat A";
        else
            A[i] = "Mouse C";
    }

    for (int i = 0; i < q; i++)
        printf("%s\n", A[i]);

    return 0;
}

int abs(int x) // calculating absolute value
{
    if (x < 0)
        return -1*x;
    else
        return x;
}