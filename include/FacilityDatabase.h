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

        bool isValidId(const std::string& id) const;
        std::string findBuilding(const std::string& name, const std::vector<std::string>& buildings) const;
    public:
        void loadFromFile(const std::string& filename, const std::vector<std::string>& buildings);
        void displayAll() const;
        void searchById(const std::string& input) const;
};


#endif