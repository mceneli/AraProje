// https://www.hackerrank.com/challenges/magic-square-forming

#include <stdio.h>

int abs(int x);
int main()
{
    int A[3][3], A2[3][3], B[4] = {2, 4, 8, 6}, C[4] = {2, 6, 8, 4}, D[8];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &A[i][j]);
    
    int cost = abs(5 - A[1][1]), cost_temp, cost_min = 100;

    for (int i = 0; i < 4; i++)
    {
        A2[0][0] = B[i % 4];
        A2[0][2] = B[(i+1) % 4];
        A2[2][2] = B[(i+2) % 4];
        A2[2][0] = B[(i+3) % 4];

        D[i] = abs(A2[0][0] - A[0][0]) + abs(A2[0][2] - A[0][2]) + abs(A2[2][2] - A[2][2]) + abs(A2[2][0] - A[2][0]);
        cost_temp = D[i] + abs(A[0][1] + A2[0][0] + A2[0][2] - 15) + abs(A[1][2] + A2[0][2] + A2[2][2] - 15) + abs(A[2][1] + A2[2][0] + A2[2][2] - 15) + abs(A[1][0] + A2[0][0] + A2[2][0] - 15);
        
        if (cost_temp < cost_min)
            cost_min = cost_temp;

        A2[0][0] = C[i % 4];
        A2[0][2] = C[(i+1) % 4];
        A2[2][2] = C[(i+2) % 4];
        A2[2][0] = C[(i+3) % 4];

        D[i+4] = abs(A2[0][0] - A[0][0]) + abs(A2[0][2] - A[0][2]) + abs(A2[2][2] - A[2][2]) + abs(A2[2][0] - A[2][0]);
        cost_temp = D[i+4] + abs(A[0][1] + A2[0][0] + A2[0][2] - 15) + abs(A[1][2] + A2[0][2] + A2[2][2] - 15) + abs(A[2][1] + A2[2][0] + A2[2][2] - 15) + abs(A[1][0] + A2[0][0] + A2[2][0] - 15);
        
        if (cost_temp < cost_min)
            cost_min = cost_temp;
    }
    
    cost += cost_min;
    printf("%d\n", cost);

    return 0;
}

int abs(int x)
{
    if (x < 0)
        return -1*x;
    else
        return x;
}