// compilation: g++ transformCode.cpp -lstdc++fs

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <experimental/filesystem>

std::set <std::string> dataTypes = {"signed", "unsigned", "char", "short", "int", "FILE"};

std::string removeComments(const std::string &path);
std::string removeSpaces(const std::string &path);
void removeQuotes(std::string &code);
void transformCode(int k, const std::string &path);
int main()
{
    std::string path = "Codes";
    int k = 5; // length of k-grams

    system("mkdir -p Transformed/Codes");

    for (const auto &code: std::experimental::filesystem::directory_iterator(path))
    {
        std::cout << code.path() << std::endl;
        std::string fullCode = removeComments(code.path());
        fullCode = removeSpaces(fullCode);
        removeQuotes(fullCode);
        std::cout << fullCode << std::endl;
        //transformCode(k, code.path());
    }

    return 0;
}

// removing comments with a GCC macro:
std::string removeComments(const std::string &path)
{
    std::array <char, 128> buffer;
    std::string result, cmd = "gcc -fpreprocessed -dD -E -P " + path;
    std::unique_ptr <FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

    if (!pipe)
        throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    return result;
}

bool skipLine(const std::string &line);
std::string removeSpaces(const std::string &fullCode)
{
    std::stringstream ss(fullCode);
    std::string line, newCode;

    while (getline(ss, line))
        if (!skipLine(line))
            newCode += line;

    newCode.erase(std::remove_if(newCode.begin(), newCode.end(), isspace), newCode.end());

    return newCode;
}

// removing contents of quotes
void removeQuotes(std::string &code)
{
    size_t pos_beg = code.find('"'), pos_end;

    while (pos_beg != std::string::npos)
    {
        pos_end = code.find('"', pos_beg+1);
        code.erase(pos_beg+1, pos_end-pos_beg-1);
        pos_beg = code.find('"', pos_beg+2);
    }

    pos_beg = code.find('\'');

    while (pos_beg != std::string::npos)
    {
        pos_end = code.find('\'', pos_beg+1);
        code.erase(pos_beg+1, pos_end-pos_beg-1);
        pos_beg = code.find('\'', pos_beg+2);
    }
}

void transformCode(int k, std::string &code)
{


    std::cout << code << std::endl;
}

// if the line begins with "#include"
bool skipLine(const std::string &line)
{
    if (line.size() == 0)
        return true;

    std::stringstream ss(line);
    std::string word;
    ss >> word;

    if (word[0] == '#')
    {
        word.erase(0, 1);

        if (word.size() == 0)
            ss >> word;

        if (word.size() >= 7 && word.substr(0, 7) == "include")
            return true;
    }

    return false;
}