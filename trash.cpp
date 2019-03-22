#include <iostream>
#include <sstream>
#include <set>
#include <map>

int main()
{
    std::stringstream ss("abc def ghi");
    std::string word;

    while (!ss.eof())
    {
        ss >> word;
        std::cout << word << std::endl;
    }
}