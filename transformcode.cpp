#include "transformcode.h"

std::unordered_set <std::string> dataTypes, conditions, loops, ignorable;

std::string transformCode(const std::string &code)
{
    std::stringstream ss(code);
    std::string finalCode, word;

    while (!ss.eof())
    {
        // dönüştürmeler
        if (ignorable.find(word) != ignorable.end() || word == "")
        {
            ss >> word;

            if (word == ";")
                ss >> word;
        }
        else if (dataTypes.find(word) != dataTypes.end())
            processDeclarations(ss, word, finalCode);
        else if (conditions.find(word) != conditions.end())
            processConditions(ss, word, finalCode);
        else if (loops.find(word) != loops.end())
            processLoops(ss, word, finalCode);
        else if (word == "typedef") // a new type declaration
            processTypedefs(ss, word);
        else if (word == "goto")
        {
            ss >> word;
            ss >> word;
            ss >> word;
        }
        else if (word == "return")
        {
            finalCode += "_r_";
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

    if (word == "struct")
        ss >> word;

    std::string name;
    ss >> name; // getting the name of the variable/function

    if (name == "{") // a struct type declaration
        while (word != "}")
            ss >> word;
    else
    {
        std::string prefix;

        // we ignore additional part of data types, like "long" int x, "const static signed" long x...
        // also if there is a pointer or a reference, we ignore it
        while (ignorable.find(name) != ignorable.end() || dataTypes.find(name) != dataTypes.end() || name[0] == '*' || name[0] == '&')
        {
            if (name[0] == '*' || name[0] == '&')
                prefix += name;

            ss >> name;
        }

        ss >> word; // getting the punctuation after the name

        // if the following punctuation is a comma or a equals sign,
        // it means that we found a variable assignment
        if (word == "," || word == "=" || word == "[")
        {
            finalCode += prefix;
            processVariableDeclarations(ss, word, finalCode);
        }

        else if (word == "(") //  a function decleration
            processFunctionDeclarations(ss);
    }

    ss >> word;
}

bool isNumber(const std::string &str)
{
    if (str[0] == 'e' && str[str.size()-1] == 'e')
        return false;

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

    return true;
}

void processVariableDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode)
{
    while (word != ";")
    {
        if (word == ",")
        {
            if (finalCode.back() == '_' || finalCode.back() == ')')
                finalCode += ';';

            ss >> word; // getting the next variable

            while (word[0] == '*' || word[0] == '&')
            {
                finalCode += word;
                ss >> word;
            }

            ss >> word;
        }
        else if (word == "=")
        {
            ss >> word;

            if (word == "{")
            {
                int numOfOpenCurlyBraces = 1;
                finalCode += "_v_=_v_";

                while (numOfOpenCurlyBraces > 0)
                {
                    ss >> word;

                    if (word == "{")
                        ++numOfOpenCurlyBraces;
                    else if (word == "}")
                        --numOfOpenCurlyBraces;
                }

                finalCode += ';';
                ss >> word;
            }
            else
                finalCode += "_v_=" + processStatement(ss, word, false);
        }
        else if (word == "[")
        {
            ss >> word;

            while (word != "]")
                ss >> word;

            ss >> word;
        }
    }
}

void processFunctionDeclarations(std::stringstream &ss)
{
    std::string word;
    ss >> word;

    while (word != ")")
        ss >> word;

    if (word == ";")
        ss >> word;
}

std::string processStatement(std::stringstream &ss, std::string &word, bool isConditionOrLoop)
{
    std::string statement;
    int numOfOpenParantheses = 1;

    while (word != "," && word != ";" && numOfOpenParantheses > 0)
    {
        if (isConditionOrLoop)
        {
            if (word == "(")
                ++numOfOpenParantheses;
            else if (word == ")")
                --numOfOpenParantheses;
        }

        if (isMathSign(word[0]) || word == "(" || word == ")" || word == "&" || word == "|" || word == "!" || word == "." || word == ":" || word == "?" || word == "->")
        {
            statement += word;
            ss >> word;
        }
        else if (word == "[")
        {
            int numOfOpenParantheses = 1;

            while (numOfOpenParantheses > 0)
            {
                ss >> word;

                if (word == "[")
                    ++numOfOpenParantheses;
                else if (word == "]")
                    --numOfOpenParantheses;
            }

            ss >> word;
        }
        else
        {
            ss >> word;

            if (word == "(")
            {
                std::string str = processFunctionCall(ss, word);
                statement += str;
                ss >> word;
            }
            else
                statement += "_v_";
        }
    }

    if (word == ";" && !isConditionOrLoop && statement.size() > 0 && (statement.back() == '_' || statement.back() == ')'))
        statement += ";";

    return statement;
}

std::string processFunctionCall(std::stringstream &ss, std::string &word)
{
    std::string equation = "_f_(";
    ss >> word;

    if (word != ")")
    {
        int numOfOpenParantheses = 1;
        equation += "_p_";

        while (numOfOpenParantheses > 0)
        {
            if (word == "(")
                ++numOfOpenParantheses;
            else if (word == ")")
                --numOfOpenParantheses;

            if (numOfOpenParantheses == 1 && word == ",")
                equation += ",_p_";

            if (numOfOpenParantheses > 0)
                ss >> word;
        }
    }

    return equation + ")";
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

void processTypedefs(std::stringstream &ss, std::string &word)
{
    ss >> word;

    if (word == "struct") // struct declaration
    {
        while (word != "}")
            ss >> word;

        ss >> word;
        dataTypes.insert(word);
        ss >> word;
    }
    else // a type name abbreviation, like "typedef unsigned long int uli;"
    {
        std::string prev;

        while (word != ";")
        {
            prev = word;
            ss >> word;
        }

        dataTypes.insert(prev);
    }

    ss >> word;
}

void initializeSets()
{
    dataTypes = {"bool", "char", "signed", "unsigned", "short", "int", "long", "size_t", "float", "double", "void", "FILE", "struct"};

    ignorable = {"const", "static", "break", "continue", "{", "}"};

    conditions = {"if", "else", "switch", "case", "default"};

    loops = {"for", "while", "do"};
}
