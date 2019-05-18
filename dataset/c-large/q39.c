// https://www.hackerrank.com/challenges/queens-attack-2

#include <stdio.h>

int main()
{
    int n, k, r_queen, c_queen, r, c;
    int left = 0, right = 0, top = 0, bottom = 0, top_left = 0, top_right = 0, bottom_left = 0, bottom_right = 0;
    scanf("%d %d", &n, &k);
    scanf("%d %d", &r_queen, &c_queen);
    int ans = (n-1)*3, row_plus, col_plus; // to determine number of suitable squares in the beginning

    if (r_queen <= n/2)
        row_plus = r_queen-1;
    else
        row_plus = n-r_queen;
    
    if (c_queen <= n/2)
        col_plus = c_queen-1;
    else
        col_plus = n-c_queen;

    if (row_plus < col_plus)
        ans += row_plus*2;
    else
        ans += col_plus*2;

    while (k--)
    {
        scanf("%d %d", &r, &c);
        
        if (r == r_queen)
        {
            if (c > c_queen && n-c+1 > right)
                right = n-c+1;
            else if (c < c_queen && c > left)
                left = c;
        }
        else if (c == c_queen)
        {
            if (r > r_queen && n-r+1 > top)
                top = n-r+1;
            else if (r < r_queen && r > bottom)
                bottom = r;
        }
        else if (c-c_queen == r-r_queen)
        {
            if (c > c_queen)
            {
                if (n-c >= n-r && n-r+1 > top_right)
                    top_right = n-r+1;
                else if (n-r > n-c && n-c+1 > top_right)
                    top_right = n-c+1;
            }
            else
            {
                if (c >= r && r > bottom_left)
                    bottom_left = r;
                else if (c < r && c > bottom_left)
                    bottom_left = c;
            }
        }
        else if (c-c_queen == r_queen-r)
        {
            if (c < c_queen)
            {
                if (n-r >= c && c > top_left)
                    top_left = c;
                else if (n-r < c && n-r+1 > top_left)
                    top_left = n-r+1;
            }
            else
            {
                if (n-c >= r && r > bottom_right)
                    bottom_right = r;
                else if (n-c < r && n-c+1 > bottom_right)
                    bottom_right = n-c+1;
            }
        }
    }

    ans -= right + left + top + bottom + top_left + top_right + bottom_left + bottom_right;

    printf("%d\n", ans);

    return 0;
}