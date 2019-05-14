#ifndef WINNOWING_H
#define WINNOWING_H

#include <unordered_map>
#include <QtDebug>
#include "transformcode.h"
#include "hashing.h"

struct Code
{
    std::string skeleton, pureCode, filePath, fileName;
    std::unordered_map <int, int> fingerprints;
    int numOfSelectedFingerPrints = 0;
};

std::vector <Code> getCodes(std::vector <std::string> codeFiles, int k, int w);
void getCodeSkeleton(Code &code);
void getFingerprints(Code &code, int k, int w);
int compareCodes(Code &code1, Code &code2);
void setFileName(Code &code);

#endif // WINNOWING_H
