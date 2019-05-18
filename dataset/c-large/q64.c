// https://www.hackerrank.com/challenges/matrix-rotation-algo

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, r, k, row = 0, col = 0;
    scanf("%d %d %d", &n, &m, &r);
    int temp_n = n, temp_m = m;
    int **A = (int **)malloc(n*sizeof(int *));

    for (int i = 0; i < n; i++)
        A[i] = malloc(m*sizeof(int));

    int min = n < m ? n : m;
    int **Spiral = (int **)malloc((min/2)*sizeof(int *));
    int **Spiral2 = (int **)malloc((min/2)*sizeof(int *));

    for (int i = 0; i < min/2; i++)
    {
        Spiral[i] = malloc((n*m)*sizeof(int));
        Spiral2[i] = malloc((n*m)*sizeof(int));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &A[i][j]);

    for (int i = 0; i < min/2; i++)
    {
        k = 0;

        for (int j = row; j < m-row; j++)
        {
            Spiral[i][k] = A[col][j];
            k++;
        }
            
        for (int j = col+1; j < n-col; j++)
        {
            Spiral[i][k] = A[j][m-row-1];
            k++;
        }

        for (int j = m-row-2; j >= row; j--)
        {
            Spiral[i][k] = A[n-col-1][j];
            k++;
        }
            
        for (int j = n-col-2; j >= col+1; j--)
        {
            Spiral[i][k] = A[j][row];
            k++;
        }

        row++, col++;
    }

    for (int i = 0; i < min/2; i++)
    {
        for (int j = 0; j < n*m-(n-2)*(m-2); j++)
            Spiral2[i][j] = Spiral[i][(j+r)%(n*m-(n-2)*(m-2))];
        
        n -= 2, m -= 2;
    }

    row = 0, col = 0, n = temp_n, m = temp_m;

    for (int i = 0; i < min/2; i++)
    {
        k = 0;

        for (int j = row; j < m-row; j++)
        {
            A[col][j] = Spiral2[i][k];
            k++;
        }
            
        for (int j = col+1; j < n-col; j++)
        {
            A[j][m-row-1] = Spiral2[i][k];
            k++;
        }

        for (int j = m-row-2; j >= row; j--)
        {
            A[n-col-1][j] = Spiral2[i][k];
            k++;
        }
            
        for (int j = n-col-2; j >= col+1; j--)
        {
            A[j][row] = Spiral2[i][k];
            k++;
        }

        row++, col++;
    }

    for (int i = 0; i < temp_n; i++)
    {
        for (int j = 0; j < temp_m; j++)
            printf("%d ", A[i][j]);

        printf("\n");
    }

    return 0;
}
