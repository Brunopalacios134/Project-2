
#include "CampusGraph.h"
#include <iostream>
using namespace std;

// Tests the campus graph independently
int main() {
    CampusGraph graph;

    graph.loadBuildings("data/buildings.txt");
    graph.loadConnections("data/connections.txt");

    cout << "\n--- Graph ---\n";
    graph.displayGraph();

    cout << "\n--- Counts and Degrees ---\n";
    graph.displayCountsAndDegrees();

    cout << "\n--- BFS from Library ---\n";
    graph.displayReachable("Library");

    cout << "\n--- BFS from Observatory ---\n";
    graph.displayReachable("Observatory");

    cout << "\n--- Shortest Path ---\n";
    graph.displayShortestPath("Library", "Gym");

    cout << "\n--- Connectivity ---\n";
    graph.displayConnectivityReport();

    return 0;
}
