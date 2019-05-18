// https://www.hackerrank.com/challenges/day-of-the-programmer

#include <stdio.h>

char *Gregorian(int year);
char *Julian(int year);
int main()
{
    int year;
    char *day = "dd.mm.yyyy";
    scanf("%d", &year);

    if (year > 1918)
        day = Gregorian(year);
    else if (year < 1918)
        day = Julian(year);
    else
    {
        printf("26.09.1917\n");
        return 0;
    }

    printf("%s%d\n", day, year);

    return 0;
}

char *Gregorian(int year)
{
    char *day;

    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
        return "12.09.";
    else
        return "13.09.";
}

char *Julian(int year)
{
    if (year % 4 == 0)
        return "12.09.";
    else
        return "13.09.";
}