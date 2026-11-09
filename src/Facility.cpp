// Facility: stores one campus facility record (ID, name, building, category)
// Author: Bruno Palacios Busnelli
#include "Facility.h"
#include <iostream>
using namespace std;

// Default constructor
Facility::Facility() {
    id = "";
    name = "";
    building = "";
    category = "";
}

// Parameterized constructor
Facility::Facility(const string& id, const string& name, const string& building, const string& category) {
    this->id = id;
    this->name = name;
    this->building = building;
    this->category = category;
}
// return id
string Facility::getId() const {
    return id;
}
// return name
string Facility::getName() const {
    return name;
}
// return building
string Facility::getBuilding() const {
    return building;
}
// return category
string Facility::getCategory() const {
    return category;
}

// Display
void Facility::display() const {
    cout << id << " | " << name << " | " << building << " | " << category << endl;
}
