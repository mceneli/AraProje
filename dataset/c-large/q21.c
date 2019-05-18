// https://www.hackerrank.com/challenges/utopian-tree

#include <stdio.h>

int main()
{
    int t, n, height; 
    scanf("%d", &t);
    
    for (int i = 0; i < t; i++)
    {
        n, height = 1; 
        scanf("%d", &n);

        for (int j = 0; j < n; j++)
        {
            if (j % 2 == 0)
                height *= 2;
            else
                height++;
        }

        printf("%d\n", height);
    }

    return 0;
}
