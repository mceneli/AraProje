#include <iostream>
#include <set>
#include <map>

int main()
{
    std::set <int> st;

    st = {1, 5, 7};

    std::cout << (st.find(1) == st.end()) << std::endl;
    std::cout << (st.find(5) == st.end()) << std::endl;
    std::cout << (st.find(7) == st.end()) << std::endl;
    std::cout << (st.find(9) == st.end()) << std::endl;
    std::cout << (st.find(2) == st.end()) << std::endl;


    std::map <int, int> mp = {std::make_pair(5, 5)};

    std::string str = "abc";
    str.append('a', 'b');

    std::cout << str << std::endl;

    return 0;
}