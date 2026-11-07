
// Tests campus graph file validation and Windows line endings
// Author: Donovan Ellis

#include "CampusGraph.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Writes test files using Windows line endings
void writeTestFile(const string& path,
                   const vector<string>& lines) {
    ofstream file(path, ios::binary);

    for (const string& line : lines) {
        file << line << "\r\n";
    }
}

int main() {
    filesystem::create_directories(
        "testdata/graph_validation");

    // Creates test data without changing the original files
    writeTestFile("testdata/graph_validation/buildings.txt", {
        "  # building comment",
        "",
        "  Library  ",
        "\tSTUDENT UNION\t",
        " Room #5 ",
        "library",
        "Bad|Extra",
        " \t ",
        "Observatory",
        "student union",
        " # another comment"
    });

    writeTestFile("testdata/graph_validation/connections.txt", {
        "# connection comment",
        "",
        "Library|Student Union",
        " Student Union | Room #5 ",
        " Room #5 | library ",
        "Library|Library",
        "student union|LIBRARY",
        "Library|Unknown Building",
        "Library| \t",
        "Library|Student Union|Extra",
        "Unknown Building|Observatory",
        " # another comment"
    });

    CampusGraph graph;
    ostringstream buildingLog, connectionLog;

    auto b = graph.loadBuildings(
        "testdata/graph_validation/buildings.txt",
        buildingLog);

    auto c = graph.loadConnections(
        "testdata/graph_validation/connections.txt",
        connectionLog);

    int passed = 0;
    int total = 0;

    // Reports each test result
    auto check = [&](bool success, const string& description) {
        ++total;

        if (success) ++passed;

        cout << (success ? "PASS: " : "FAIL: ")
             << description << '\n';
    };

    // File loading tests
    check(b.accepted == 4 && b.rejected == 3,
          "Buildings: 4 accepted, 3 rejected");

    check(c.accepted == 3 && c.rejected == 6,
          "Connections: 3 accepted, 6 rejected");

    check(graph.getBuildingCount() == 4,
          "Four unique buildings");

    check(graph.getConnectionCount() == 3,
          "Three undirected connections");

    // Building search tests
    string name;

    check(graph.findBuilding(" library ", name)
          && name == "Library",
          "Case-insensitive building search");

    check(graph.findBuilding("student union", name)
          && name == "STUDENT UNION",
          "Original building spelling preserved");

    check(graph.findBuilding("room #5", name)
          && name == "Room #5",
          "# inside a building name");

    check(graph.findBuilding("Observatory", name)
          && name == "Observatory",
          "Windows line endings handled");

    // Graph display tests
    ostringstream display;
    graph.displayGraph(display);

    check(display.str().find(
          "Library: STUDENT UNION, Room #5") != string::npos,
          "Neighbor insertion order");

    check(display.str().find(
          "Observatory: (no connections)") != string::npos,
          "Isolated building display");

    ostringstream degrees;
    graph.displayCountsAndDegrees(degrees);

    check(degrees.str().find(
          "Library: degree 2") != string::npos
          && degrees.str().find(
          "Observatory: degree 0") != string::npos,
          "Correct building degrees");

    // Validation warning tests
    check(buildingLog.str().find("line 6:") != string::npos
          && buildingLog.str().find("line 7:") != string::npos
          && buildingLog.str().find("line 10:") != string::npos,
          "Building warnings include line numbers");

    check(connectionLog.str().find("line 6:") != string::npos
          && connectionLog.str().find("line 7:") != string::npos
          && connectionLog.str().find("line 8:") != string::npos
          && connectionLog.str().find("line 9:") != string::npos
          && connectionLog.str().find("line 10:") != string::npos
          && connectionLog.str().find("line 11:") != string::npos,
          "Connection warnings include line numbers");

    // BFS tests
    ostringstream bfs;

    check(graph.displayReachable("  library  ", bfs)
          && bfs.str().find(
          "Reachable: 3 of 4 buildings") != string::npos,
          "BFS reachable count");

    const string text = bfs.str();

    auto l = text.find("Library (distance 0)");
    auto s = text.find("STUDENT UNION (distance 1)");
    auto r = text.find("Room #5 (distance 1)");

    check(l != string::npos
          && s != string::npos
          && r != string::npos
          && l < s && s < r,
          "BFS follows neighbor order");

    // Shortest path tests
    ostringstream path;

    check(graph.displayShortestPath(
          "Library", "Room #5", path)
          && path.str().find(
          "Number of connections: 1") != string::npos,
          "Shortest path works");

    ostringstream disconnected;

    check(!graph.displayShortestPath(
          "Library", "Observatory", disconnected),
          "Disconnected path handled");

    check(graph.getComponentCount() == 2,
          "Two connected components");

    // Empty graph test
    CampusGraph emptyGraph;
    ostringstream emptyDisplay;
    emptyGraph.displayGraph(emptyDisplay);

    check(emptyDisplay.str().find(
          "No buildings") != string::npos
          && emptyGraph.getComponentCount() == 0,
          "Empty graph handled safely");

    cout << "\nResults: " << passed
         << "/" << total << " tests passed\n";

    return passed == total ? 0 : 1;
}
