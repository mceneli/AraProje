// https://www.hackerrank.com/challenges/two-pluses

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, k, p = 0, max = 1, max2 = 1, max_ans = 1;
    scanf("%d %d", &n, &m);
    char A[n][m];
    int Plus[n*m][3];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c", &A[i][j]);

    for (int i = 1; i < n-1; i++)
        for (int j = 1; j < m-1; j++)
            if (A[i][j] == 'G')
            {
                k = 1;

                while (i+k < n && i-k >= 0 && j+k < m && j-k >= 0)
                {
                    if (A[i][j+k] == 'G' && A[i][j-k] == 'G' && A[i+k][j] == 'G' && A[i-k][j] == 'G')
                    {
                        Plus[p][0] = 4*k+1;
                        Plus[p][1] = i;
                        Plus[p][2] = j;
                        p++;
                    }
                    else
                        break;

                    k++;
                }
            }

    for (int i = 0; i < p; i++)
    {
        max = Plus[i][0];     
        max2 = 1;

        for (int j = 0; j < p; j++)
            if (j != i && Plus[j][0] <= max && Plus[j][0] > max2)
            {
                if (Plus[i][1] == Plus[j][1] && abs(Plus[i][2]-Plus[j][2]) <= (Plus[i][0]-1)/4 + (Plus[j][0]-1)/4)
                    continue;

                if (Plus[i][2] == Plus[j][2] && abs(Plus[i][1]-Plus[j][1]) <= (Plus[i][0]-1)/4 + (Plus[j][0]-1)/4)
                    continue;

                if (Plus[j][2] <= Plus[i][2]+(Plus[i][0]-1)/4 && Plus[j][2] >= Plus[i][2]-(Plus[i][0]-1)/4)
                    if (Plus[i][1] <= Plus[j][1]+(Plus[j][0]-1)/4 && Plus[i][1] >= Plus[j][1]-(Plus[j][0]-1)/4)
                        continue;

                if (Plus[j][1] <= Plus[i][1]+(Plus[i][0]-1)/4 && Plus[j][1] >= Plus[i][1]-(Plus[i][0]-1)/4)
                    if (Plus[i][2] <= Plus[j][2]+(Plus[j][0]-1)/4 && Plus[i][2] >= Plus[j][2]-(Plus[j][0]-1)/4)
                        continue;

                max2 = Plus[j][0];
            }

        if (max*max2 > max_ans)
            max_ans = max*max2;
    }

    printf("%d\n", max_ans);

    return 0;
}