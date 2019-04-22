#include <stdio.h>

double anotherFunction(long var1, long var2, long var3);
int main()
{
    short a = 10, b = 5, c = 25;

    double res = anotherFunction(a, b, c);

    if (res > 0)
    {
        for (size_t iter = 0; iter < 10; ++iter)
            printf("%d\n", 10);

        printf("\n");
    }
    else if (res == 0)
        printf("another zero");
    else
    {
        size_t iter = 0;

        while (iter < 1)
            printf("%d\n", iter);

        res = anotherFunction(a, b, c) + 15 * 4;
    }

    return 0;
}

double anotherFunction(long var1, long var2, long var3)
{
    double res;
    res = var1*var2+var3;
    return res;
}