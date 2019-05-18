// https://www.hackerrank.com/challenges/happy-ladybugs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int g;
    scanf("%d", &g);

    while (g--)
    {
        int ABC[26] = {0}, n, unhappy = 0, underlines = 0;
        scanf("%d", &n);
        char *b = (char *)malloc(512000*sizeof(char));
        scanf("%s", b);

        for (int i = 0; i < n; i++)
        {
            if (b[i] != '_')
                ABC[b[i] - 'A']++;
            else
                underlines++;
        }

        for (int i = 0; i < 26; i++)
            if (ABC[i] == 1)
            {
                unhappy = 1;
                break;
            }

        if (underlines == 0)
        {
            if (b[0] != b[1] || b[n-2] != b[n-1])
                unhappy = 1;
            else
            {
                for (int i = 1; i < n-1; i++)
                    if (b[i] != b[i-1] && b[i] != b[i+1])
                    {
                        unhappy = 1;
                        break;
                    }
            }
        }

        if (unhappy == 0)
            printf("YES\n");
        else
            printf("NO\n");        
    }

    return 0;
}