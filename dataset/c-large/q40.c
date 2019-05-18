// https://www.hackerrank.com/challenges/acm-icpc-team

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, score, max = 0, teams = 1;
    scanf("%d %d", &n, &m);
    char *A[n];

    for (int i = 0; i < n; i++)
    {
        A[i] = (char *)malloc(1024*sizeof(char));
        scanf("%s", A[i]);
    }

    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            score = 0;

            for (int k = 0; k < m; k++)
                if (A[i][k] == '1' || A[j][k] == '1')
                    score++;

            if (score > max)
            {
                max = score;
                teams = 1;
            }
            else if (score == max)
                teams++;
        }
    }

    printf("%d\n%d\n", max, teams);

    return 0;
}