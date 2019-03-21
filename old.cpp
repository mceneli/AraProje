// compilation: g++ transformCode.cpp -lstdc++fs

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <experimental/filesystem>

std::set <std::string> ignorable, keywords, functions;
std::map <std::string, std::string> dataTypes;
std::map <std::string, std::string> variables;

std::string removeComments(const std::string &path);
std::string removeSpaces(const std::string &path);
void removeQuotes(std::string &code);
std::string transformCode(int k, const std::string &code);
void initializeSets();
int main()
{
    std::string path = "Codes";
    int k = 5; // length of k-grams

    initializeSets();

    system("mkdir -p Transformed/Codes");

    for (const auto &code: std::experimental::filesystem::directory_iterator(path))
    {
        std::cout << code.path() << std::endl;
        std::string path = code.path();
        std::string fullCode = removeComments(path);
        fullCode = removeSpaces(fullCode);
        removeQuotes(fullCode);
        std::cout << fullCode << "\n";
        std::string finalCode = transformCode(k, fullCode);
        std::cout << finalCode << "\n\n";
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

std::string insertCurlyBraces(std::string &code)
{
    std::stringstream ss(code);
    std::string newCode, word;
    std::stack <int> braceStack;



    return newCode;
}

void processVariables(std::stringstream &ss, std::string &dataType, std::string &varName, std::string &punct, std::string &finalCode);
void processFunctionDeclarations(std::stringstream &ss, std::string &funcName, std::string &finalCode);
std::string transformCode(int k, const std::string &code)
{
    std::stringstream ss(code);
    std::string finalCode, word;

    while (ss >> word)
    {
        // dönüştürmeler
        if (dataTypes.find(word) != dataTypes.end())
        {
            // a data type dedected, it may specify a variable or a function decleration
            std::string name, punct;
            ss >> name; // getting the name of the variable/function

            if (name[0] == '*') // if there is a pointer, ignore it
                ss >> name;

            ss >> punct; // getting the punctuation after the name

            // if the following punctuation is a comma, semicolon or a equals sign, 
            // it means that we found a variable
            if (punct == "," || punct == ";" || punct == "=")
                processVariables(ss, word, name, punct, finalCode);
            else if (punct == "(")
                processFunctionDeclarations(ss, name, finalCode);
        }
    }

    return finalCode;
}

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

void processVariables(std::stringstream &ss, std::string &dataType, std::string &varName, std::string &punct, std::string &finalCode)
{
    variables.insert(std::make_pair(varName,  dataTypes[dataType]));
    std::string word = punct, equation;
    
    while (word != ";")
    {
        if (word == ",")
        {
            finalCode += ',';
            ss >> varName; // getting the next variable

            if (varName[0] == '*') // if there is a pointer, ignore it
                ss >> varName;

            variables.insert(std::make_pair(varName, dataTypes[dataType]));
            ss >> word;
        }
        else if (word == "=")
        {
            equation = dataTypes[dataType] + "=";
            ss >> word;

            while (word != "," && word != ";")
            {
                if (isNumber(word))
                    equation += "_int_";
                else if (variables.find(word) != variables.end())
                    equation += variables[word]; // adding the data type of the word
                else
                    equation += word;

                ss >> word;
            }
            
            finalCode += equation;
        }

        //ss >> word;
    }

    finalCode += ';';
}

void processFunctionDeclarations(std::stringstream &ss, std::string &funcName, std::string &finalCode)
{
    std::string word;
    ss >> word;

    while (word != ")")
        ss >> word;

    if (functions.find(funcName) == functions.end())
        functions.insert(funcName);
}

void initializeSets()
{
    dataTypes = {std::make_pair("bool", "_boo_"), 
                 std::make_pair("char", "_chr_"),
                 std::make_pair("wchar_t", "_chr_"), // wide char data type
                 std::make_pair("short", "_int_"),
                 std::make_pair("signed", "_int_"),
                 std::make_pair("unsigned", "_int_"),
                 std::make_pair("int", "_int_"),
                 std::make_pair("long", "_int_"),
                 std::make_pair("void", "_voi_"),
                 std::make_pair("FILE", "_fil_")};

    ignorable = {"const", "static"};

    keywords = {"if", "else", "switch", "case", "for", "while", "do", "break", "continue", "goto", 
                "inline", "extern", "true", "false", "struct", "typedef", "include", "define", "return"};

    functions = {"assert", "isalnum", "isalpha", "iscntrl", "isdigit", "isgraph", "islower", "isprint",
                 "ispunct", "isspace", "isupper", "isxdigit", "tolower", "toupper", "errno", "localeconv",
                 "setlocale", "acos", "asin", "atan", "atan2", "ceil", "cos", "cosh", "exp", "fabs", "floor", "fmod",
                 "frexp", "ldexp", "log", "log10", "modf", "pow", "sin", "sinh", "sqrt", "tan", "tanh", "jmp_buf",
                 "longjmp", "setjmp", "raise", "signal", "sig_atomic_t", "va_arg", "va_end", "va_start",
                 "clearerr", "fclose", "feof", "ferror", "fflush", "fgetc", "fgetpos", "fgets", "fopen",
                 "fprintf", "fputc", "fputs", "fread", "freopen", "fscanf", "fseek", "fsetpos", "ftell",
                 "fwrite", "getchar", "getch", "getc", "main", "gets", "perror", "printf", "putc", "putchar", "puts", "remove",
                 "rename", "rewind", "scanf", "setbuf", "setvbuf", "sprintf", "sscanf", "tmpfile", "tmpnam",
                 "ungetc", "vfprintf", "vprintf", "vsprintf", "abort", "abs", "atexit", "atof", "atoi", "atol",
                 "bsearch", "calloc", "div", "exit", "free", "getenv", "labs", "ldiv", "malloc", "mblen", "mbstowcs",
                 "mbtowc", "qsort", "rand", "realloc", "srand", "strtod", "strtol", "strtoul", "system",
                 "wcstombs", "wctomb", "memchr", "memcmp", "memcpy", "memmove", "memset", "strcat", "strchr",
                 "strcmp",", ""strcoll", "strcpy", "strcspn", "strerror", "strlen", "strncat", "strncmp",
                 "strncpy", "strpbrk", "strrchr", "strspn", "strstr", "strtok", "strxfrm", "asctime",
                 "clock", "ctime", "difftime", "gmtime", "localtime", "mktime", "strftime", "time"};
}