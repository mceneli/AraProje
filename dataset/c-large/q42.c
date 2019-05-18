// https://www.hackerrank.com/challenges/organizing-containers-of-balls

#include <stdio.h>

int main()
{
    int q;
    scanf("%d", &q);

    while (q--)
    {
        int n, flag, sum = 0;
        scanf("%d", &n);
        int A[n][n], Rows[n], Cols[n];

        for (int i = 0; i < n; i++)
            Rows[i] = 0, Cols[i] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &A[i][j]);
                Rows[i] += A[i][j];
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Cols[i] += A[j][i];   

        for (int i = 0; i < n; i++)
        {
            flag = 0;

            for (int j = 0; j < n; j++)
            {
                if (Rows[i] == Cols[j])
                {
                    Cols[j] = 0;
                    flag++;
                    sum++;
                    break;
                }
            }
            
            if (flag == 0)
                break;
        }

        if (sum == n)
            printf("Possible\n");
        else
            printf("Impossible\n");       
    }

    return 0;
}