#include "hashing.h"

long long getFactor(int k)
{
    long long factor = 1;

    for (int i = 0; i < k; i++)
        factor = (factor * PRIME_BASE) % PRIME_MOD;

    return factor;
}

long long positiveMod(long long x, long long y)
{
    long long ans = x % y;

    return ans >= 0 ? ans : ans + y;
}

std::vector <long long> karpRabinHashing(const std::string &str, int k, long long factor)
{
    std::vector <long long> hashKeys;

    long long key = 0;

    for (int i = 0; i < k; ++i)
        key = (key*PRIME_BASE + str[i]) % PRIME_MOD;

    hashKeys.push_back(key);

    for (int i = k; i < str.size(); i++)
    {
        key = positiveMod(key*PRIME_BASE + str[i] - factor*str[i-k], PRIME_MOD);
        hashKeys.push_back(key);
    }

    return hashKeys;
}
