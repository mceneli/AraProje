#include <iostream>
#include <sstream>
#include <set>
#include <map>

bool isNumber(const std::string &str)
{
    int num_of_e = 0; // the number may be in form of 1e10, 1e15, 2e3...

    for (int i = 0; i < str.size(); ++i)
        if (!isdigit(str[i]))
        {
            if (str[i] == 'e')
            {
                ++num_of_e;

                if (num_of_e > 1)
                    return false;
            }
            else
                return false;
        }

    return num_of_e == 0 ? true : str[0] != 'e' && str[str.size()-1] != 'e' ? true : false;
}

int main()
{
    std::cout << isNumber("e34") << std::endl;

    return 0;
}