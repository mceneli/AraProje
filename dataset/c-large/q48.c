// https://www.hackerrank.com/challenges/the-time-in-words

#include <stdio.h>

int main()
{
    int h, m;
    scanf("%d %d", &h, &m);
    char *nums[] = {0, "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                    "twelve", "thirteen", "fourteen", "quarter", "sixteen", "seventeen", "eighteen", "nineteen",
                    "twenty", "twenty one", "twenty two", "twenty three", "twenty four", "twenty five", "twenty six",
                    "twenty seven", "twenty eight", "twenty nine"};

    if (m == 0)
        printf("%s o' clock\n", nums[h]);
    else if (m == 15)
        printf("quarter past %s\n", nums[h]);
    else if (m == 30)
        printf("half past %s\n", nums[h]);
    else if (m == 45)
        printf("quarter to %s\n", nums[h+1]);
    else if (m <= 30)
        printf("%s minutes past %s\n", nums[m], nums[h]);
    else if (m > 30)
        printf("%s minutes to %s\n", nums[60-m], nums[h+1]);

    return 0;
}