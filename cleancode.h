#ifndef CLEANCODE_H
#define CLEANCODE_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>
#include <memory>

std::string removeComments(const std::string &path);
std::string removeSpaces(const std::string &fullCode);
bool skipLine(const std::string &line);
bool isMathSign(char ch);
std::string formatLine(const std::string &line);
void removeQuotes(std::string &code);

#endif // CLEANCODE_H
