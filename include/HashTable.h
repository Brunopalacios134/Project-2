#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <string>
#include "Facility.h"
const size_t DEFAULT_CAPACITY = 11;

class HashTable{
    private:
    std::vector<std::vector<Facility>> buckets;
    size_t capacity;
    size_t count;
    size_t collisions;
    size_t hashFunction(const std::string& key) const;

    public:
    HashTable(size_t capacity = DEFAULT_CAPACITY);
    // Inserts a facility into the hash table
    bool insert(const Facility& facility);
    // Returns true if the facility is found.
    bool search(const std::string& id, Facility& result) const;
    // Returns the capacity of the hash table.
    size_t getCapacity() const;
    // Returns the number of facilities stored.
    size_t getCount() const;
    // Returns the number of collisions.
    size_t getCollisions() const;
};
#endif