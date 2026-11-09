// Unit test for Utils
// Author: Bruno Palacios Busnelli
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

int main() {
    cout << "[" << trim("  Library \r") << "]" << endl;
    cout << "[" << trim("     ") << "]" << endl;

    cout << toUpper("f004") << endl;
    cout << toUpper("Room 101") << endl;

    vector<string> parts = split("F004|Computer Lab A|Science Building|Computer Lab", '|');

    cout << "Fields: " << parts.size() << endl;

    for (const string& piece : parts) {
        cout << "[" << piece << "]" << endl;
    }

    vector<string> parts2 = split("A||B", '|');

    cout << "Fields: " << parts2.size() << endl;

    return 0;
}