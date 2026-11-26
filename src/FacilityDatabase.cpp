// FacilityDatabase: loads and validates facilities.txt, keeps facilities in file
// order, and searches by ID using the custom HashTable
// Author: Bruno Palacios Busnelli
#include "FacilityDatabase.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
// Checks if the facility ID has a valid format
bool FacilityDatabase::isValidId(const string& id) const{
    if(id.length() != 4){
        return false;
    }
    if(id[0] != 'F'){
        return false;
    }
    for(int i = 1; i<=3; i++){
        if(!isdigit((unsigned char)id[i])){
            return false;
        }
    }
    return true;
}
// Finds a building from the building list
string FacilityDatabase::findBuilding(const string& name, const vector<string>& buildings) const {
    for (const string& b : buildings) {
        if (toUpper(b) == toUpper(name)) {
            return b;
        }
    }

    return "";
}

// Load facilities from file
void FacilityDatabase::loadFromFile(const string& filename, const vector<string>& buildings) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open file " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected (hash capacity "
             << table.getCapacity() << ", entries "
             << table.getCount() << ", collisions "
             << table.getCollisions() << ")" << endl;
        return;
    }
    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;
    while (getline(file, line)) {
        lineNumber++;
        string clean = trim(line);
        if (clean.empty() || clean[0] == '#') {
            continue;
        }
        vector<string> parts = split(clean, '|');
        if (parts.size() != 4) {
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": expected 4 fields, found " << parts.size() << endl;
            rejected++;
            continue;
        }
        for (string& part : parts) {
            part = trim(part);
        }
        bool hasEmptyField = false;
        for (const string& part : parts) {
            if (part.empty()) {
                hasEmptyField = true;
                break;
            }
        }
        if (hasEmptyField) {
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": empty required field" << endl;
            rejected++;
            continue;
        }
        string id = toUpper(parts[0]);
        if (!isValidId(id)) {
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": invalid ID " << id
                 << " (must be F followed by 3 digits)" << endl;
            rejected++;
            continue;
        }
        string official = findBuilding(parts[2], buildings);
        if (official.empty()) {
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": unknown building " << parts[2] << endl;
            rejected++;
            continue;
        }
        Facility facility(id, parts[1], official, parts[3]);
        if (!table.insert(facility)) {
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": duplicate facility ID " << id << endl;
            rejected++;
            continue;
        }
        facilities.push_back(facility);
        accepted++;
    }
    cout << filename << ": " << accepted << " accepted, "
         << rejected << " rejected (hash capacity "
         << table.getCapacity() << ", entries "
         << table.getCount() << ", collisions "
         << table.getCollisions() << ")" << endl;
}
// Displays all facilities
void FacilityDatabase::displayAll() const {
    if (facilities.empty()) {
        cout << "No facilities loaded." << endl;
        return;
    }
    for (const Facility& f : facilities) {
        f.display();
    }
    cout << "Total facilities: " << facilities.size() << endl;
}
// Searches for a facility using its ID
void FacilityDatabase::searchById(const string& input) const {
    string id = toUpper(trim(input));
    if (id.empty()) {
        cout << "Error: ID cannot be blank." << endl;
        return;
    }
    if (!isValidId(id)) {
        cout << "Invalid format: an ID is F followed by exactly three digits." << endl;
        return;
    }
    Facility result;
    if (table.search(id, result)) {
        cout << "Found: ";
        result.display();
    } else {
        cout << "Not found: no facility with ID " << id << endl;
    }
}
// Searches for facilities by name
void FacilityDatabase::searchByName(const string& input) const {
    string target = toUpper(trim(input));
    if (target.empty()) {
        cout << "Error: facility name cannot be blank." << endl;
        return;
    }
    int count = 0;
    for (const Facility& f : facilities) {
        if (toUpper(f.getName()) == target) {
            f.display();
            count++;
        }
    }
    if (count == 0) {
        cout << "No facilities found with name: " << trim(input) << endl;
    }
    cout << "Matches: " << count << endl;
}
// Searches for facilities by category
void FacilityDatabase::searchByCategory(const string& input) const {
    string target = toUpper(trim(input));
    if (target.empty()) {
        cout << "Error: category cannot be blank." << endl;
        return;
    }
    int count = 0;
    for (const Facility& f : facilities) {
        if (toUpper(f.getCategory()) == target) {
            f.display();
            count++;
        }
    }
    if (count == 0) {
        cout << "No facilities found in category: " << trim(input) << endl;
    }
    cout << "Matches: " << count << endl;
}
// Displays a report of facilities grouped by category
void FacilityDatabase::displayCategoryReport() const {
    int total = facilities.size();
    if (total == 0) {
        cout << "No facilities are available." << endl;
        cout << "Total: 0" << endl;
        return;
    }
    vector<string> categoryNames;
    vector<int> counts;
    for (const Facility& f : facilities) {
        string key = toUpper(f.getCategory());
        bool found = false;
        for (size_t i = 0; i < categoryNames.size(); i++) {
            if (toUpper(categoryNames[i]) == key) {
                counts[i]++;
                found = true;
                break;
            }
        }
        if (!found) {
            categoryNames.push_back(f.getCategory());
            counts.push_back(1);
        }
    }
    cout << "Category | Count | Percentage" << endl;
    for (size_t i = 0; i < categoryNames.size(); i++) {
        double percent = counts[i] * 100.0 / total;
        cout << categoryNames[i] << " | "
             << counts[i] << " | "
             << fixed << setprecision(1) << percent << "%" << endl;
    }
    cout << "Total | " << total << " | 100.0%" << endl;
}