#  include     <stdio.h>

struct Shape
{
    int w, h;
};

typedef struct
{
    int age;
    char *name;
} Person;

typedef long long int lli;

int main()
{
    struct Shape sh = {1, 2};// = 5;
    Person person = {15, "Osman"};
    int x, y;
    //x = 1, y = 1;

    lli z = 10;
    int x;
    label:
    x = 5 + abs(-3, 4), y = 1;
    x = 2*x;
    goto label;
    //#define x 5

    int A[5] = {5};
    int y = A[0] + 5;

    switch (abs(5))
    {
        case 1:
            x++;
            break;

        case 2:
            x++;
            break;
    
        default:
            break;
    }

    if (x != 0)
        x = x+1;

    for (int i = 0; i < 10; ++i)
        while (i--)
            if (i > 0)
                printf("");

    do
        ++x;
    while (x > 0);
    
    return 0;
}