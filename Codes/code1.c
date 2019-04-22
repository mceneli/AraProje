#  include     <stdio.h>
#include <stdlib.h>

typedef struct
{
    int age;
    int salary;
} Job;

int main()
{
    Job *job = (Job *)malloc(sizeof(Job)*abs(abs(5)), abs(4), 4+7, 2*abs(4));

    job->age = 1500;

    int a, b, c = 30;
    a = 10;
    b = 40;

    int A[5][3];

    A[A[0][0]][A[0][0]] = 5;

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