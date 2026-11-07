//Author: Bruno Palacios

#include <iostream>
#include <vector>
#include <string>
#include "FacilityDatabase.h"

using namespace std;

int main() {
    vector<string> buildings = {
        "Library",
        "Student Union",
        "Science Building",
        "Engineering Building",
        "Business Building",
        "Gym",
        "Observatory"
    };

    FacilityDatabase db;

    db.loadFromFile("data/facilities.txt", buildings);

    db.displayAll();

    db.searchById("F004");
    db.searchById("f004");
    db.searchById("004");
    db.searchById("F999");
    db.searchById("   ");

    // Test missing file
    FacilityDatabase db2;

    db2.loadFromFile("data/nope.txt", buildings);
    db2.displayAll();

    return 0;
}