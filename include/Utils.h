// Utility functions shared by all modules
// Author: Bruno Palacios Busnelli
#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
// Returns a copy of the string with leading and trailing whitespace (space, tab, \r) removed
std::string trim(const std::string&);
// Converts a string to uppercase.
std::string toUpper(const std::string& str);

std::vector<std::string> split(const std::string& line, char delimiter);
#endif