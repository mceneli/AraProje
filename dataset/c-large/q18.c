// https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, k = 1;
    scanf("%d", &n);
    int *Scores = malloc((n+1)*sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &Scores[i]);

    Scores[n] = -1;

    for (int i = 1; i < n; i++)
        if (Scores[i-1] != Scores[i])
            k++;

    scanf("%d", &m);
    int *Alice = malloc(m*sizeof(int));
    int Alice_ranking = k+1, ind = n-1;

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &Alice[i]);

        for (int j = ind; j >= 0; j--)
        {
            if (Alice[i] >= Scores[j])
                ind--;
            else
                break;

            if (Alice[i] >= Scores[j] && Scores[j] != Scores[j+1])
                Alice_ranking--;
        }

        printf("%d\n", Alice_ranking);
    }

    return 0;
}