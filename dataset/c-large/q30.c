// https://www.hackerrank.com/challenges/extra-long-factorials/problem

#include <gmp.h>
#include <stdio.h>

int main() 
{
    int n;
    scanf("%d", &n);

    mpz_t out;
    mpz_init(out);
    mpz_fac_ui(out, n);
    mpz_out_str(stdout, 10, out);
    printf("\n");

    return 0;
}