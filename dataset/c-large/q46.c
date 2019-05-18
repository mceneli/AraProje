// https://www.hackerrank.com/challenges/beautiful-triplets

#include <stdio.h>

int main()
{
    int n, d, beauty = 0;
    scanf("%d %d", &n, &d);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n-2; i++)
    {
        for (int j = i+1; j < n-1; j++)
        {
            if (A[j] - A[i] == d)
            {
                for (int k = j+1; k < n; k++)
                {
                    if (A[k] - A[j] == d)
                        beauty++;
                    else if (A[k] - A[j] > d)
                        break;
                }
            }
            else if (A[j] - A[i] > d)
                break;
        }
    }

    printf("%d\n", beauty);
    
    return 0;
}