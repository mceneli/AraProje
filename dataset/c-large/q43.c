// https://www.hackerrank.com/challenges/encryption

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    char *s = (char *)malloc(10240*sizeof(char));
    scanf("%s", s);
    int len = strlen(s), f_len = floor(sqrt(len)), c_len = ceil(sqrt(len)), row, col;

    if (f_len * f_len >= len)
        row = f_len, col = f_len;
    else if (f_len * c_len >= len)
        row = f_len, col = c_len;
    else
        row = c_len, col = c_len;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col, i + j*col < len; j++)
            printf("%c", s[i + j*col]);

        printf(" ");
    }

    return 0;
}