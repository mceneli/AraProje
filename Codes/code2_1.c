#  include     <stdio.h>
#include <stdlib.h>

typedef struct
{
    int age;
    int salary;
} Job;

int main()
{
    int a, b, c = 30;
    a = 10;
    b = 40;

    printf("%d\n", a*b+c);

    int x;

    if (x == 0)
        printf("zero");
    else if (x == 1)
        printf("one");
    else
        printf("two");

    int i;

    for (i = 0; i < 10; ++i)
        printf("%d\n", i);
    
    return 0;
}