// compilation: g++ transformCode.cpp -lstdc++fs

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <experimental/filesystem>

std::set <std::string> ignorable, keywords;
std::map <std::string, std::string> dataTypes, variables;

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
        std::cout << fullCode << "\n\n";
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
std::string formatLine(const std::string &line);
std::string removeSpaces(const std::string &fullCode)
{
    std::stringstream ss(fullCode);
    std::string line, newCode, result;

    while (getline(ss, line))
        if (!skipLine(line))
            newCode += formatLine(line);          

    std::unique_copy(newCode.begin(), newCode.end(), std::back_insert_iterator <std::string> (result), 
                     [] (char a, char b) { return isspace(a) && isspace(b);});

    return result;
}

bool isMathSign(char ch) { return ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'; };
std::string formatLine(const std::string &line)
{
    std::string formattedLine;
    int j = 0;

    while (j < line.size())
    {
        if (j+1 < line.size() && ((line[j] == '-' && line[j+1] == '>') || (isMathSign(line[j]) && isMathSign(line[j+1]))))
        {
            formattedLine.push_back(' ');
            formattedLine.push_back(line[j]);
            formattedLine.push_back(line[j+1]);
            formattedLine.push_back(' ');
            ++j;
        }
        else if (line[j] != '_' && ispunct(line[j]))
        {
            formattedLine.push_back(' ');
            formattedLine.push_back(line[j]);
            formattedLine.push_back(' ');
        }
        else
            formattedLine.push_back(line[j]);

        ++j;
    }

    return formattedLine;
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
    std::stringstream ss(code);
    std::string word;

    while (ss >> word)
    {
        // dönüştürmeler
    }
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


void initializeSets()
{
    dataTypes = {std::make_pair("bool", "_bool_"), 
                 std::make_pair("char", "_char_"),
                 std::make_pair("wchar_t", "_char_"), // wide char data type
                 std::make_pair("short", "_int_"),
                 std::make_pair("signed", "_int_"),
                 std::make_pair("unsigned", "_int_"),
                 std::make_pair("int", "_int_"),
                 std::make_pair("long", "_int_"),
                 std::make_pair("void", "_void_"),
                 std::make_pair("FILE", "_file_")};

    ignorable = {"const", "static"};

    keywords = {"if", "else", "switch", "case", "for", "while", "do", "break", "continue", "goto", 
                "inline", "extern", "true", "false", "struct", "typedef", "return"};
}