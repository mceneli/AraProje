#ifndef TRANSFORMCODE_H
#define TRANSFORMCODE_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

#include "cleancode.h"

#include <QtDebug>

std::string transformCode(const std::string &code);
bool isNumber(const std::string &str);
void processDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode);
void processVariableDeclarations(std::stringstream &ss, std::string &word, std::string &finalCode);
void processFunctionDeclarations(std::stringstream &ss);
std::string processStatement(std::stringstream &ss, std::string &word, bool isConditionOrLoop);
std::string processFunctionCall(std::stringstream &ss, std::string &word);
void processConditions(std::stringstream &ss, std::string &word, std::string &finalCode);
void processLoops(std::stringstream &ss, std::string &word, std::string &finalCode);
void processTypedefs(std::stringstream &ss, std::string &word);
void initializeSets();

#endif
