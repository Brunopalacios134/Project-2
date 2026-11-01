// Utility functions shared by all modules
// Author: Bruno Palacios Busnelli
#ifndef UTILS_H
#define UTILS_H
#include <string>
// Returns a copy of the string with leading and trailing whitespace (space, tab, \r) removed
std::string trim(const std::string&);
// Converts a string to uppercase.
std::string toUpper(const std::string& str);

#endif