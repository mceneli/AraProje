// compilation: g++ transformCode.cpp -lstdc++fs

/*
    Yapılacaklar Listesi:
    + değişken tanımlamaları
    + fonksiyon tanımlamaları
    + koşullu ifadeler
    + döngüler
    + işlemler
    - noktalı virgüller
    - struct erişimleri: ".", "->"
    - diziler: A[]
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <experimental/filesystem>

std::set <std::string> dataTypes, ignorable, keywords, functions, conditions, loops;

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

bool skipLine(const std::string &line) { return line.size() == 0 || line[0] == '#'; }
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

bool isMathSign(char ch) { return ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '>' || ch == '<'; }
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

std::string processStatement(std::stringstream &ss, std::string &word, bool isConditionOrLoop);
std::string processFunctionCall(std::stringstream &ss);
void processDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode);
void processVariableDeclarations(std::stringstream &ss, std::string &punct, std::string &finalCode);
void processFunctionDeclarations(std::stringstream &ss, std::string &funcName, std::string &finalCode);
void processConditions(std::stringstream &ss, std::string &word, std::string &finalCode);
void processLoops(std::stringstream &ss, std::string &word, std::string &finalCode);
std::string transformCode(int k, const std::string &code)
{
    std::stringstream ss(code);
    std::string finalCode, word;

    while (!ss.eof())
    {
        // dönüştürmeler
        if (ignorable.find(word) != ignorable.end() || word == "")
            ss >> word;
        else if (dataTypes.find(word) != dataTypes.end())
            processDeclarations(ss, word, finalCode);
        else if (conditions.find(word) != conditions.end())
            processConditions(ss, word, finalCode);
        else if (loops.find(word) != loops.end())
            processLoops(ss, word, finalCode);
        else if (word == "return")
        {
            finalCode += "_r_";
            ss >> word;
        }
        else if (word == ";")
        {
            finalCode += ";";
            ss >> word;
        }
        else
        {
            finalCode += processStatement(ss, word, false);
            ss >> word;
        }
    }

    return finalCode;
}

void processDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode)
{
    // a data type dedected, it may specify a variable or a function decleration
    std::string name;
    ss >> name; // getting the name of the variable/function

    // we ignore the additional data types, like long int x, const static signed long x...
    // also if there is a pointer or a reference, ignore it
    if (ignorable.find(name) != ignorable.end() || dataTypes.find(name) != dataTypes.end() || name[0] == '*' || name[0] == '&') 
        ss >> name;

    ss >> word; // getting the punctuation after the name

    // if the following punctuation is a comma or a equals sign, 
    // it means that we found a variable assignment
    if (word == "," || word == "=")
        processVariableDeclarations(ss, word, finalCode);
    else if (word == "(") //  a function decleration
        processFunctionDeclarations(ss, name, finalCode);

    ss >> word;
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

void processVariableDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode)
{
    std::string equation;
    
    while (word != ";")
    {
        if (word == ",")
        {
            finalCode += ',';
            ss >> word; // getting the next variable

            if (word[0] == '*' || word[0] == '&') // if there is a pointer or a reference, ignore it
                ss >> word;

            ss >> word;
        }
        else if (word == "=")
        {
            ss >> word;
            finalCode += "_v_=" + processStatement(ss, word, false);;
        }
    }

    finalCode += ';';
}

std::string processStatement(std::stringstream &ss, std::string &word, bool isConditionOrLoop)
{
    std::string statement;
    int numOfOpenParantheses = 1;

    while (word != "," && word != ";" && numOfOpenParantheses > 0)
    {
        if (functions.find(word) != functions.end()) // function call
            statement += processFunctionCall(ss);
        else if (isMathSign(word[0]) || word == "(" || word == ")" || word == "&" || word == "|")
            statement += word;
        else
            statement += "_v_";

        if (isConditionOrLoop)
        {
            if (word == "(")
                ++numOfOpenParantheses;
            else if (word == ")")
                --numOfOpenParantheses;
        }

        ss >> word;
    }

    /*if (word == ";")
        statement += ";";*/

    return statement;
}

std::string processFunctionCall(std::stringstream &ss)
{
    std::string equation = "_f_(", word;
    ss >> word; // '(' character
    ss >> word;

    while (word != ")")
    {
        equation += "_p_";
        ss >> word;

        while (word != ")" && word != ",")
            ss >> word;

        if (word == ",")
            equation += ",";
    }

    return equation + ")";
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

void processConditions(std::stringstream &ss, std::string &word, std::string &finalCode)
{
    if (word == "switch")
    {
        ss >> word;
        ss >> word;
        processStatement(ss, word, true);
        ss >> word;
    }
    else if (word == "case")
    {
        finalCode += "_c_(_v_==_v_)";
        ss >> word;
        ss >> word;
        ss >> word;
    }
    else if (word == "default")
    {
        finalCode += "_c_()";
        ss >> word;
        ss >> word;
    }
    else
    {
        bool isElse = (word == "else");
        ss >> word;
            
        if (isElse && word != "if")
            finalCode += "_c_()";
        else
        {
            if (word == "if") // the condition is "else if"
                ss >> word; // getting '(' character

            ss >> word;
            finalCode += "_c_(" + processStatement(ss, word, true);

            //ss >> word;
        }
    }
}

void processLoops(std::stringstream &ss, std::string &word, std::string &finalCode)
{
    if (word == "for")
    {
        ss >> word;

        while (word != ";")
            ss >> word;

        ss >> word;

        finalCode += "_l_(" + processStatement(ss, word, true) + ")";

        ss >> word;
        processStatement(ss, word, true);
    }
    else if (word == "while")
    {
        ss >> word;
        ss >> word;
        finalCode += "_l_(" + processStatement(ss, word, true);
    }
    else // do while
    {
        finalCode += "_l_()";
        ss >> word;
    }
}

void initializeSets()
{
    dataTypes = {"bool", "char", "signed", "unsigned", "short", "int", "long", "void", "FILE"};

    ignorable = {"include", "define", "struct", "const", "static", "break", "continue", "{", "}"};

    conditions = {"if", "else", "switch", "case", "default"};

    loops = {"for", "while", "do"};

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