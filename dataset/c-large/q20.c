// https://www.hackerrank.com/challenges/designer-pdf-viewer

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int letter, i = 0, max = 1, width = 0, area = 0;
    int *H = malloc(sizeof(int)*26);

    for (int i = 0; i < 26; i++)
       scanf("%d", &H[i]);

    char* word = (char *)malloc(512000*sizeof(char));
    scanf("%s", word);

    while (1)
    {
        letter = (char)word[i] - 'a';

        if (word[i] == ' ' || word[i] == '\0')
        {
            area += max*width;
            max = 1;
            width = 0;

            if (word[i] == '\0')
                break;
        }
        else if (H[letter] > max)
            max = H[letter];

        width++;
        i++;
    }

    printf("%d\n", area);

    return 0;
}