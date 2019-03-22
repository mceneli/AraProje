#  include     <stdio.h>

int aFunction(int x, int y)
{
    return x+y;
}

int main()
{
    int x = 3, y =  5 + aFunction(5, x) + y;
    int C = 1 + rand() % 10; // number of coming customers
    int L = 1 + rand() % 5; // number of leaving customers

    if ((x > 0) && (5 > 0))
        x = 2*x;
    else if (x < 0)
        x++;
    else if (x < 1)
    {
        if (x > 0 && x < 0)
        {

        }
    }
    else
        x--;

    int a = 5;

    switch (a)
    {
        case 0:
            x++;
            break;
        case 1:
            x--;
            break;
        default:
            break;
    }

    return 0;
}