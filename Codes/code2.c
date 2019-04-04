#  include     <stdio.h>

int main()
{
    int a = 10;
    short b = 30;
    long c = 40;

    printf("%d\n", a*b+c);
    
    int x;

    switch (x)
    {
        case 0:
            printf("zero");
            break;

        case 1:
            printf("one");
            break;
    
        default:
            printf("two");
    }

    int i;

    while (i < 10)
    {
        printf("%d\n", i);
        ++i;
    }
    
    return 0;
}