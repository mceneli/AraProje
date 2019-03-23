#  include     <stdio.h>

int main()
{
    int x = 5 + abs(-3, 4);
    x = 2*x;

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

    for (int i = 0; i < 10; ++i)
        while (i--)
            if (i > 0)
                printf("");

    do
        ++x;
    while (x > 0);
    
    return 0;
}