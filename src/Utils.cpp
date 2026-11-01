// Utility functions shared by all modules
// Author: Bruno Palacios Busnelli
#include "Utils.h"
#include <string>
#include <cctype>
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
string toUpper(const string& str){
    string result = str;
    for (size_t i = 0; i < result.length(); i++){
        result[i] = toupper(result[i]);
    }
    return result;
}

