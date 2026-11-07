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
    std::string getId() const;
    std::string getName() const;
    std::string getBuilding() const;
    std::string getCategory() const;

    // Displays facility information
    void display() const;
};

#endif