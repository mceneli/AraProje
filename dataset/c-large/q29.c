// https://www.hackerrank.com/challenges/find-digits

#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        int n, score = 0;
        scanf("%d", &n);
        int temp = n;

        while (temp > 0)
        {
            if ((temp % 10) != 0 && n % (temp % 10) == 0)
                score++;
            
            temp /= 10;
        }

        printf("%d\n", score);
    }

    return 0;
}