// https://www.hackerrank.com/challenges/the-grid-search

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t, R, C, r, c, flag;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d %d", &R, &C);
        char **G = malloc(R*sizeof(char *));

        for (int i = 0; i < R; i++)
        {
            G[i] = (char *)malloc(10240*sizeof(char));
            scanf("%s", G[i]);
        }

        scanf("%d %d", &r, &c);
        char **P = malloc(r*sizeof(char *));

        for (int i = 0; i < r; i++)
        {
            P[i] = (char *)malloc(10240*sizeof(char));
            scanf("%s", P[i]);
        }

        for (int i = 0; i <= R-r; i++)
        {
            for (int j = 0; j <= C-c; j++)
            {
                flag = 0;

                for (int k = i; k < i+r; k++)
                {
                    for (int m = j; m < j+c; m++)
                    {
                        if (G[k][m] != P[k-i][m-j])
                        {
                            flag++;
                            break;
                        }
                    }

                    if (flag != 0)
                        break;
                }

                if (flag == 0)
                    break;
            }

            if (flag == 0)
                break;
        }

        if (flag == 0)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}