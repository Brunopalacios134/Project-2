// HashTable: custom hash table keyed by facility ID
// Author: Bruno Palacios Busnelli
#include "HashTable.h"
using namespace std;


HashTable::HashTable(size_t capacity){
    if(capacity == 0){
        capacity = DEFAULT_CAPACITY;
    }
    this->capacity = capacity;
    buckets.resize(capacity);
    count = 0;
    collisions = 0;
}
size_t HashTable::hashFunction(const string& key) const {
    unsigned long long hash = 0;
    for (char c : key) {
        hash = (hash * 31 + (unsigned char)c) % capacity;
    }
    return hash;
}
// Inserts a facility into the hash table
bool HashTable::insert(const Facility& facility) {
    string id = facility.getId();
    size_t index = hashFunction(id);
    for (const Facility& f : buckets[index]) {
        if (f.getId() == id) {
            return false;
        }
    }
    if (!buckets[index].empty()) {
        collisions++;
    }
    buckets[index].push_back(facility);
    count++;
    return true;
}
// Returns true if the facility is found.
bool HashTable::search(const string& id, Facility& result) const {
    size_t index = hashFunction(id);
    for (const Facility& f : buckets[index]) {
        if (f.getId() == id) {
            result = f;
            return true;
        }
    }
    return false;
}
// Returns the capacity of the hash table.
size_t HashTable::getCapacity() const {
    return capacity;
}
// Returns the number of facilities stored.
size_t HashTable::getCount() const {
    return count;
}
// Returns the number of collisions.
size_t HashTable::getCollisions() const {
    return collisions;
}
