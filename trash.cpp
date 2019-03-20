#include <iostream>
#include <sstream>
#include <set>
#include <map>

void dosome(std::stringstream &ss)
{
    std::string word;
    ss >> word;
    std::cout << word << std::endl;
    ss >> word;
    std::cout << word << std::endl;
}

int main()
{
    std::stringstream ss("abc def ghi jkl");

    std::string word;
    ss >> word;
    std::cout << word << std::endl;
    dosome(ss);
    ss >> word;
    std::cout << word << std::endl;

    return 0;
}