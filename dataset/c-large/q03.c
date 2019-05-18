// https://www.hackerrank.com/challenges/kangaroo

#include <stdio.h>

int main()
{
    int x1, x2, v1, v2, bigger, smaller, big_v, sm_v;
    char *result;
    scanf("%d %d %d %d", &x1, &v1, &x2, &v2);

    if (x1 > x2)
    {
        bigger = x1;
        big_v = v1;
        smaller = x2;
        sm_v = v2;

        if (v1 > v2)
            result = "NO";
    }   
    else
    {
        bigger = x2;
        big_v = v2;
        smaller = x1;
        sm_v = v1;
        
        if (v2 > v1)
            result = "NO";
    }

    while (smaller < bigger)
    {
        smaller += sm_v;
        bigger += big_v;
    }

    if (smaller == bigger)
        result = "YES";
    else
        result = "NO";

    printf("%s\n", result);

    return 0;
}