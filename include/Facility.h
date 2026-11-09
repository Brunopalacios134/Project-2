// Facility: stores one campus facility record (ID, name, building, category)
// Author: Bruno Palacios Busnelli
#ifndef FACILITY_H
#define FACILITY_H

#include <string>

class Facility {
private:
    std::string id;
    std::string name;
    std::string building;
    std::string category;

public:
    // Constructors
    Facility();
    Facility(const std::string& id, const std::string& name, const std::string& building, const std::string& category);

    // Getters
    // return id
    std::string getId() const;
    // return name
    std::string getName() const;
    // return building
    std::string getBuilding() const;
    // return category
    std::string getCategory() const;

    // Displays facility information
    void display() const;
};

#endif