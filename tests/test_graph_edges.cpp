
#include "CampusGraph.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Tests graph errors and edge cases
// Author: Donovan Ellis

int main() {
    CampusGraph graph;
    int passed = 0;
    int total = 0;

    // Shows whether each test passed
    auto check = [&](bool result, const string& name) {
        ++total;
        if (result) {
            ++passed;
            cout << "PASS: " << name << '\n';
        } else {
            cout << "FAIL: " << name << '\n';
        }
    };

    ostringstream output;

    // Load sample data
    auto buildings = graph.loadBuildings(
        "data/buildings.txt", output);
    auto connections = graph.loadConnections(
        "data/connections.txt", output);

    check(buildings.accepted == 7,
          "Load 7 buildings");

    check(connections.accepted == 6,
          "Load 6 connections");

    // Case-insensitive building search
    string name;
    check(graph.findBuilding("  lIbRaRy  ", name)
              && name == "Library",
          "Case-insensitive building search");

    // Reject duplicate buildings
    string error;
    check(!graph.addBuilding("library", &error)
              && graph.getBuildingCount() == 7,
          "Duplicate building rejected");

    // Reject blank building names
    check(!graph.addBuilding("   ", &error),
          "Blank building rejected");

    // Reject unknown buildings
    check(!graph.addConnection(
              "Library", "Unknown Building", &error),
          "Unknown connection rejected");

    // Reject self-connections
    check(!graph.addConnection(
              "Library", "library", &error),
          "Self-connection rejected");

    // Reject reversed duplicate connections
    check(!graph.addConnection(
              "Gym", "Student Union", &error)
              && graph.getConnectionCount() == 6,
          "Reversed duplicate rejected");

    // Test unknown BFS starting building
    ostringstream bfsOutput;
    check(!graph.displayReachable(
              "Unknown Building", bfsOutput),
          "Unknown BFS start rejected");

    // Test isolated building
    ostringstream isolatedOutput;
    graph.displayReachable("Observatory", isolatedOutput);
    check(isolatedOutput.str().find(
              "Reachable: 1 of 7") != string::npos,
          "Isolated building BFS");

    // Test disconnected buildings
    ostringstream pathOutput;
    check(!graph.displayShortestPath(
              "Library", "Observatory", pathOutput),
          "Disconnected path rejected");

    // Test same start and destination
    ostringstream sameOutput;
    graph.displayShortestPath(
        "Library", "Library", sameOutput);
    check(sameOutput.str().find(
              "Number of connections: 0") != string::npos,
          "Same-building shortest path");

    // Test unknown destination
    ostringstream unknownOutput;
    check(!graph.displayShortestPath(
              "Library", "Unknown", unknownOutput),
          "Unknown destination rejected");

    // Test missing file
    CampusGraph emptyGraph;
    ostringstream missingOutput;
    auto missing = emptyGraph.loadBuildings(
        "testdata/nonexistent_buildings.txt",
        missingOutput);

    check(missing.accepted == 0
              && emptyGraph.getBuildingCount() == 0
              && missingOutput.str().find(
                  "Error: cannot open") != string::npos,
          "Missing file handled");

    cout << "\nResults: " << passed
         << "/" << total << " tests passed\n";

    return passed == total ? 0 : 1;
}
