#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

int closestPrimeNumber(int x);

// A hash table class which designed for Karp-Rabin algorithm.
struct HashTableKR
{
    int R = 31; // a constant for Horner's String Hashing Method
    int M, lastFactor;
    std::vector <std::vector <std::pair <std::string, int>>> table;

    HashTableKR() = default;

    HashTableKR(int N)
    {
        M = closestPrimeNumber(N);
        table.resize(M);
        //R %= M;
    }

    HashTableKR(int N, int K): HashTableKR(N)
    {
        setLastFactor(K);
    }

    void setLastFactor(int K)
    {
        lastFactor = 1;

        for (int i = 0; i < K-1; ++i)
            lastFactor = (lastFactor * R) % M;
    }

    int hash(const std::string &str);
    int hash(const std::string &str, int prevKey, char prevChar);
    void insert(const std::string &str, int key = -1);
    int find(const std::string &str, int key = -1);
};

int mainXXX()
{
    int N = 100, K = 25;
    //int N = 10, K = 5;
    HashTableKR hashTable(N, K);
    
    // _v_=_v_*_v_-(_v_*_v_*_v_);_c_(_v_<_v_)_r_-_v_;_c_()*_v_=(-_v_-_f_(_p_))/(_v_*_v_);*_v_=(-_v_+_f_(_p_))/(_v_*_v_);_r__v_;_f_(_p_,_p_,_p_,_p_);_f_(_p_);_c_(_v_==_v_)_f_(_p_,_p_);_c_()_c_(_f_(_p_,_p_,_p_,_p_,_p_)==-_v_)_f_(_p_);_c_()_f_(_p_,_p_);_f_(_p_,_p_);_f_();_r__v_;
    std::string para = {"_v_=_v_*_v_-(_v_*_v_*_v_);_c_(_v_<_v_)_r_-_v_;_c_()*_v_=(-_v_-_f_(_p_))/(_v_*_v_);*_v_=(-_v_+_f_(_p_))/(_v_*_v_);_r__v_;_f_(_p_,_p_,_p_,_p_);_f_(_p_);_c_(_v_==_v_)_f_(_p_,_p_);_c_()_c_(_f_(_p_,_p_,_p_,_p_,_p_)==-_v_)_f_(_p_);_c_()_f_(_p_,_p_);_f_(_p_,_p_);_f_();_r__v_;"};

    int prevKey = -1;
    char prevChar = 0;

    std::cout << (int)'o' << " " << (int)'s' << " " << (int)'m' << " " << (int)'a' << " " << (int)'n' << std::endl;

    for (int i = 0; i < para.size()-K+1; ++i)
        hashTable.insert(para.substr(i, K));

    for (int i = 0; i < hashTable.table.size(); ++i)
        for (int j = 0; j < hashTable.table[i].size(); ++j)
            std::cout << "(" << i << "," << j << "): " << hashTable.table[i][j].first << " - " << hashTable.table[i][j].second << std::endl;

    return 0;
}

int HashTableKR::hash(const std::string &str)
{
    int key = 0, mul = 1;

    for (const char &ch: str)
    {
        key = (key + ch * mul) % M;
        mul = (mul * R) % M;
    }

    return key;
}

inline int mod(int x, int y)
{
    int ans = x % y;
    return ans >= 0 ? ans : ans+y;
}

int HashTableKR::hash(const std::string &str, int prevKey, char prevChar)
{
    return mod((prevKey - (prevChar % M)) / R + (str[str.size()-1] % M) * lastFactor, M);
}

void HashTableKR::insert(const std::string &str, int key)
{
    if (key == -1)
        key = hash(str);

    //int key = (prevKey == -1) ? hash(str) : hash(str, prevKey, prevChar);
    int indice = find(str, key);

    if (indice == -1)
        table[key].push_back({str, 1});
    else
        ++table[key][indice].second;

   // prevKey = key;
    //prevChar = str[0];
}

int HashTableKR::find(const std::string &str, int key)
{
    if (key == -1)
        key = hash(str);

    for (size_t i = 0; i < table[key].size(); ++i)
        if (table[key][i].first == str)
            return i;

    return -1;
}

bool isPrime(int x)
{
    int denominator = 3;

    while (denominator <= sqrt(x))
    {
        if (x % denominator == 0)
            return false;

        denominator += 2;
    }

    return true;;
}

int closestPrimeNumber(int x)
{
    if (x == 2)
        return 2;

    int num = (x % 2 == 0) ? x+1 : x;

    while (!isPrime(num))
        num += 2;

    return num;
}