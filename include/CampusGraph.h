
#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

// Campus graph and BFS functions
// Author: Donovan Ellis

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class CampusGraph {
public:
    struct LoadSummary {
        std::size_t accepted;
        std::size_t rejected;

        LoadSummary() : accepted(0), rejected(0) {}
    };

    CampusGraph();

    // Adds a building
    bool addBuilding(const std::string& name,
                     std::string* error = nullptr);

    // Connects two buildings
    bool addConnection(const std::string& from,
                       const std::string& to,
                       std::string* error = nullptr);

    // Loads building data
    LoadSummary loadBuildings(const std::string& filePath,
                              std::ostream& out = std::cout);

    // Loads connection data
    LoadSummary loadConnections(const std::string& filePath,
                                std::ostream& out = std::cout);

    // Finds a building by name
    bool findBuilding(const std::string& name,
                      std::string& canonicalName) const;

    // Shows buildings and connections
    void displayGraph(std::ostream& out = std::cout) const;

    // Shows building counts and degrees
    void displayCountsAndDegrees(
        std::ostream& out = std::cout) const;

    // Finds reachable buildings using BFS
    bool displayReachable(const std::string& start,
                          std::ostream& out = std::cout) const;

    // Finds shortest path using BFS
    bool displayShortestPath(
        const std::string& start,
        const std::string& destination,
        std::ostream& out = std::cout) const;

    // Shows graph connectivity
    void displayConnectivityReport(
        std::ostream& out = std::cout) const;

    // Returns building count
    std::size_t getBuildingCount() const;

    // Returns connection count
    std::size_t getConnectionCount() const;

    // Returns connected component count
    std::size_t getComponentCount() const;

private:
    struct Building {
        std::string name;
        std::vector<std::size_t> neighbors;

        explicit Building(const std::string& buildingName)
            : name(buildingName) {}
    };

    std::vector<Building> buildings;
    std::size_t connectionCount;

    // Finds a building's index
    int buildingIndex(const std::string& name) const;

    // Skips blank lines and comments
    static bool skipLine(const std::string& line);
};

#endif
