// Utility functions shared by all modules
// Author: Bruno Palacios Busnelli
#include "Utils.h"
#include <string>
#include <iostream>
using namespace std;
string trim(const string& str){
    string whitespace = " \t\r";
    size_t start = str.find_first_not_of(whitespace);
    if (start == string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(whitespace);

    size_t length = end - start + 1;

    return str.substr(start, length);
}

