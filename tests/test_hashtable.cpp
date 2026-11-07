#include <iostream>
#include "HashTable.h"
#include "Facility.h"
using namespace std;
int main() {
    HashTable table;
    table.insert(Facility("F001", "Main Reading Room", "Library", "Library"));
    table.insert(Facility("F002", "Tutoring Center", "Library", "Tutoring Center"));
    table.insert(Facility("F003", "Student Services Office", "Student Union", "Student Services Office"));
    table.insert(Facility("F004", "Computer Lab A", "Science Building", "Computer Lab"));
    table.insert(Facility("F005", "Room 101", "Engineering Building", "Classroom"));
    table.insert(Facility("F006", "Computer Lab B", "Engineering Building", "Computer Lab"));
    table.insert(Facility("F007", "Room 101", "Business Building", "Classroom"));
    table.insert(Facility("F008", "Fitness Center", "Gym", "Recreation"));
    table.insert(Facility("F009", "Room 205", "Science Building", "Classroom"));
    table.insert(Facility("F010", "Research Help Desk", "Library", "Library"));
    cout << "Capacity: " << table.getCapacity() << endl;
    cout << "Entries: " << table.getCount() << endl;
    cout << "Collisions: " << table.getCollisions() << endl;
    Facility result;
    if (table.search("F004", result)) {
        cout << "Found: " << endl;
        result.display();
    }
    if (!table.search("F999", result)) {
        cout << "Not found: F999" << endl;
    }
    bool ok = table.insert(Facility("F004", "Fake", "Gym", "Other"));
    cout << "Duplicate inserted? " << ok << endl;
    cout << "Collisions after duplicate: "
         << table.getCollisions() << endl;
    if (table.search("F004", result)) {
        result.display();
    }
    return 0;
}