// https://www.hackerrank.com/challenges/bomber-man

#include <stdio.h>

int main()
{
    int r, c, n;
    scanf("%d %d %d", &r, &c, &n);
    char A[r+2][c+2], B[r+2][c+2], C[r+2][c+2];

    for (int i = 0; i < c+2; i++)
    {
        A[0][i] = '.', B[0][i] = '.';
        A[r+1][i] = '.', B[r+1][i] = '.';
    }

    for (int i = 1; i < r+1; i++)
    {
        A[i][0] = '.', B[i][0] = '.';
        A[i][c+1] = '.', B[i][c+1] = '.';
    }

    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            scanf(" %c", &A[i][j]);

    if (n == 1)
    {
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
                printf("%c", A[i][j]);

            printf("\n");
        }
    }
    else if (n % 2 == 0)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                printf("O");

            printf("\n");
        }
    }
    else
    {      
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                if (A[i][j] == '.')
                {
                    if (A[i][j+1] == '.' && A[i][j-1] == '.' && A[i-1][j] == '.' && A[i+1][j] == '.')
                        B[i][j] = 'O';
                    else
                        B[i][j] = '.';
                }
                else
                    B[i][j] = '.';
            }
        }

        if (n % 4 == 3)
            for (int i = 1; i <= r; i++)
            {
                for (int j = 1; j <= c; j++)
                    printf("%c", B[i][j]);

                printf("\n");
            }   
        else
        {
            for (int i = 1; i <= r; i++)
            {
                for (int j = 1; j <= c; j++)
                {
                    if (B[i][j] == '.')
                    {
                        if (B[i][j+1] == '.' && B[i][j-1] == '.' && B[i-1][j] == '.' && B[i+1][j] == '.')
                            C[i][j] = 'O';
                        else
                            C[i][j] = '.';
                    }
                    else
                        C[i][j] = '.';
                }
            }

            for (int i = 1; i <= r; i++)
            {
                for (int j = 1; j <= c; j++)
                    printf("%c", C[i][j]);

                printf("\n");
            }
        }
    }

    return 0;
}