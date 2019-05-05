// compilation: g++ winnowing.cpp -lstdc++fs

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <experimental/filesystem>

#include "transformCode.hpp"
#include "hashing.hpp"

struct Code
{
    std::string skeleton, fileName;
    std::unordered_map <int, int> fingerprints;
    int numOfSelectedFingerPrints = 0;
};

std::vector <Code> getCodes(std::string &path, int k, int w);
int compareCodes(Code &code1, Code &code2);
int main()
{
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    const auto before = clock::now();

    std::string path = "dataset";

    initializeSets();

    int k = 20, w = 5;
    std::vector <Code> codes = getCodes(path, k, w);

    for (Code &code: codes)
        std::cout << code.fileName << ":\n" << code.skeleton << "\n\n" << std::endl;

    for (int i = 0; i < codes.size()-1; ++i)
    {
        for (int j = i+1; j < codes.size(); ++j)
        {
            double sameFingerprints = compareCodes(codes[i], codes[j]);
            std::cout << sameFingerprints << " " << codes[i].numOfSelectedFingerPrints << " " << codes[j].numOfSelectedFingerPrints << std::endl;
            int rate1 = 100 * sameFingerprints / (codes[i].numOfSelectedFingerPrints);
            int rate2 = 100 * sameFingerprints / (codes[j].numOfSelectedFingerPrints);
            std::cout << "similarity of " << codes[i].fileName << " to " << codes[j].fileName << ": " << rate1 << "\n";
            std::cout << "similarity of " << codes[j].fileName << " to " << codes[i].fileName << ": " << rate2 << "\n\n";
        }
    }

    const auto duration = std::chrono::duration_cast<ms>(clock::now() - before);

    std::cout << "It took " << duration.count()/1000.0 << "ms" << std::endl;

    return 0;
}

void getCodeSkeleton(Code &code);
void getFingerprints(Code &code, int k, int w);
std::vector <Code> getCodes(std::string &path, int k, int w)
{
    std::vector <Code> codes;

    for (const auto &codeFile: std::experimental::filesystem::directory_iterator(path))
    {
        Code *code = new Code;
        code->fileName = codeFile.path();
        getCodeSkeleton(*code);
        getFingerprints(*code, k, w);
        codes.push_back(*code);
    }

    return codes;
}

void getCodeSkeleton(Code &code)
{
    std::string fullCode = removeComments(code.fileName);
    fullCode = removeSpaces(fullCode);
    removeQuotes(fullCode);
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