// Utility functions shared by all modules
// Author: Bruno Palacios Busnelli
#include "Utils.h"
#include <string>
#include <cctype>
#include <vector>
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
vector<string> split(const string& line, char delimiter) {
    vector<string> pieces;
    size_t start = 0;

    size_t pos = line.find(delimiter, start);
    while (pos != string::npos) {
        pieces.push_back(line.substr(start, pos - start));

        start = pos + 1;
        pos = line.find(delimiter, start);
    }

    pieces.push_back(line.substr(start));

    return pieces;
}

