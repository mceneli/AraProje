// https://www.hackerrank.com/challenges/almost-sorted

#include <stdio.h>

int main()
{
    int n, l, r, flag = 0, flag2 = 0;
    scanf("%d", &n);
    int A[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    if (n == 2 && A[0] > A[1])
    {
        printf("yes\nswap 1 2\n");
        flag2++;
    }

    for (int i = 1; i < n; i++)
    {
        if (A[i] < A[i-1])
        {
            l = i-1;
            break;
        }
        else
            flag++;
    }

    if (flag2 == 0 && flag == n-1)
    {
        printf("yes\n");
        flag2++;
        return 0;
    }

    if (flag2 == 0)
    {
        for (int i = l+2; i < n; i++)
            if (A[i] > A[i-1])
            {
                r = i-1;
                
                if (A[r] > A[l-1] && A[r+1] > A[l])
                {
                    flag = 0;

                    for (int j = r+2; j < n; j++)
                        if (A[j] < A[j-1])
                        {
                            flag++;
                            break;
                        }

                    if (flag == 0)
                    {
                        printf("yes\n");

                        if (r-l != 1)
                            printf("reverse %d %d\n", l+1, r+1);
                        else
                            printf("swap %d %d\n", l+1, r+1);

                        flag2++;
                    }
                }
    
                break;
            }
    }

    if (flag2 == 0)
    {
        for (int i = l+2; i < n; i++)
            if (A[i] < A[i-1])
            {
                r = i;
                
                if (A[r] > A[l-1] && A[r+1] > A[l])
                {
                    flag = 0;

                    for (int j = r+2; j < n; j++)
                        if (A[j] < A[j-1])
                        {
                            flag++;
                            break;
                        }

                    if (flag == 0)
                    {
                        printf("yes\nswap %d %d\n", l+1, r+1);
                        flag2++;
                    }
                }
    
                break;
            }
    }

    if (flag2 == 0)
        printf("no\n");

    return 0;
}