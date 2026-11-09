// FacilityDatabase: loads and validates facilities.txt, keeps facilities in file
// order, and searches by ID using the custom HashTable
// Author: Bruno Palacios Busnelli
#ifndef FACILITYDATABASE_H
#define FACILITYDATABASE_H

#include <string>
#include <vector>
#include "Facility.h"
#include "HashTable.h"

class FacilityDatabase{
    private:
        HashTable table;
        std::vector<Facility> facilities;
        // Checks if the facility ID has a valid format
        bool isValidId(const std::string& id) const;
        // Finds a building from the building list
        std::string findBuilding(const std::string& name, const std::vector<std::string>& buildings) const;
    public:
        // Loads facilities from a file
        void loadFromFile(const std::string& filename, const std::vector<std::string>& buildings);
        // Displays all facilities
        void displayAll() const;
        // Searches for a facility using its ID
        void searchById(const std::string& input) const;
};


#endif