#   include <stdio.h>

int aFunction(int x,   int   y ,  int  z);


void aFunction2(char  ch  , char * str);
int aFunction3(int   x);

int main() {
    int  x =        10;
    int     y = 5;
    int   z =           25;

        int ans =    aFunction(x, y, z);

    if (ans > 0)
    {
        for (int i =        0; i <    10; ++i)
        {
                        printf("%d\n", 10);
        }

    printf("\n");
    }
    else if (ans == 0)
    {
        printf("zero");
    }
    else
    {
            int j = 0;

    while (j < 1)
                        printf("%d\n", j);

        ans     =      aFunction(x,   y  ,  z)+15*4;
    }



    return   0;
}

        int aFunction(int   x   ,  int  y  , int   z)
{
    int   ans = x *  y +  z;
    return ans;
}

void     aFunction2(char   ch, char *   str){
    str[  0  ]      = ch;
    str[strlen(str) -   1]  = ch;}

int aFunction3(int x){if (x > 0) return x; else return -x;}