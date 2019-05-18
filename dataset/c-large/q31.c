// https://www.hackerrank.com/challenges/append-and-delete

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k, result, j = 0, s_size = 0, t_size = 0;
    char* s = (char*)malloc(512000*sizeof(char));
    char* t = (char*)malloc(512000*sizeof(char)); 
    scanf("%s %s", s, t);    
    scanf("%d",&k);

    while (s[s_size] != '\0')
        s_size++;
    while (t[t_size] != '\0')
        t_size++;
    while ((s[j] == t[j]) && s[j] != '\0' && t[j] != '\0') 
        j++; // num of same chars

    result = (s_size - j) + (t_size - j);

    if (k == result)
        printf("Yes\n");
    else if (k > result)
    {
        if ((k - result - 2*j) > 0)
            printf("Yes\n");
        else if ((k - result) % 2 == 0)
            printf("Yes\n");
        else
            printf("No\n");
    }
    else
        printf("No\n");

    return 0;
}