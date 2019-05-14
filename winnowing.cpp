#include "winnowing.h"

std::vector <Code> getCodes(std::vector <std::string> codeFiles, int k, int w)
{
    std::vector <Code> codes;

    for (const auto &codeFile: codeFiles)
    {
        initializeSets();
        Code *code = new Code;
        code->filePath = codeFile;
        qDebug() << codeFile.c_str();
        getCodeSkeleton(*code);
        qDebug() << "getCodeSkeleton";
        getFingerprints(*code, k, w);
        qDebug() << "getFingerprints";
        setFileName(*code);
        codes.push_back(*code);
    }

    return codes;
}

void getCodeSkeleton(Code &code)
{
    std::string fullCode = removeComments(code.filePath);
    fullCode = removeSpaces(fullCode);
    removeQuotes(fullCode);
    code.pureCode = fullCode;
    code.skeleton = transformCode(fullCode);
}

void getFingerprints(Code &code, int k, int w)
{
    // Applying Karp-Rabin algorithm:
    long long factor = getFactor(k);
    std::vector <long long> hashKeys = karpRabinHashing(code.skeleton, k, factor);

    // Applying Winnowing algorithm:
    int min = -1; // index of minimum hash

    for (int i = 0; i < hashKeys.size()-w+1; ++i)
    {
        if (min < i) // the previous minimum hash key is no longer in the window
        {
            min = std::min_element(hashKeys.begin()+i, hashKeys.begin()+i+w) - hashKeys.begin();
            ++code.fingerprints[hashKeys[min]];
            ++code.numOfSelectedFingerPrints;
        }
        else if (hashKeys[i+w-1] <= hashKeys[min]) // the previous minimum hash key is still in the window
        {
            min = i+w-1;
            ++code.fingerprints[hashKeys[min]];
            ++code.numOfSelectedFingerPrints;
        }
    }
}

int compareCodes(Code &code1, Code &code2)
{
    int tokens_matched = 0;

    for (const auto &p1: code1.fingerprints)
    {
        auto p2 = code2.fingerprints.find(p1.first);

        if (p2 != code2.fingerprints.end())
            tokens_matched += std::min(p1.second, p2->second);
    }

    return tokens_matched;
}

void setFileName(Code &code)
{
    auto index = code.filePath.find_last_of('/');

    if (index != std::string::npos)
        code.fileName = code.filePath.substr(index+1, code.filePath.size()-index-2);
}
