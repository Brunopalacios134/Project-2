
// Campus graph and BFS implementation
// Author: Donovan Ellis

#include "CampusGraph.h"
#include "Utils.h"

#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

// Creates an empty graph
CampusGraph::CampusGraph() : connectionCount(0) {}

// Finds a building by name
int CampusGraph::buildingIndex(const string& name) const {
    const string key = toUpper(trim(name));

    if (key.empty()) return -1;

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (toUpper(buildings[i].name) == key) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// Skips blank and comment lines
bool CampusGraph::skipLine(const string& line) {
    const string cleaned = trim(line);
    return cleaned.empty() || cleaned[0] == '#';
}

// Adds a building
bool CampusGraph::addBuilding(const string& name, string* error) {
    const string cleaned = trim(name);

    if (cleaned.empty()) {
        if (error) *error = "empty building name";
        return false;
    }

    if (buildingIndex(cleaned) != -1) {
        if (error) *error = "duplicate building: " + cleaned;
        return false;
    }

    buildings.push_back(Building(cleaned));
    return true;
}

// Adds a connection between buildings
bool CampusGraph::addConnection(
    const string& from,
    const string& to,
    string* error) {

    const string first = trim(from);
    const string second = trim(to);

    if (first.empty() || second.empty()) {
        if (error) *error = "empty connection endpoint";
        return false;
    }

    const int a = buildingIndex(first);
    const int b = buildingIndex(second);

    if (a < 0) {
        if (error) *error = "unknown building: " + first;
        return false;
    }

    if (b < 0) {
        if (error) *error = "unknown building: " + second;
        return false;
    }

    if (a == b) {
        if (error) *error = "self-connection";
        return false;
    }

    const vector<size_t>& neighbors =
        buildings[static_cast<size_t>(a)].neighbors;

    if (find(neighbors.begin(), neighbors.end(),
             static_cast<size_t>(b)) != neighbors.end()) {
        if (error) *error = "duplicate connection";
        return false;
    }

    buildings[static_cast<size_t>(a)].neighbors.push_back(
        static_cast<size_t>(b));

    buildings[static_cast<size_t>(b)].neighbors.push_back(
        static_cast<size_t>(a));

    ++connectionCount;
    return true;
}

// Loads buildings from a file
CampusGraph::LoadSummary CampusGraph::loadBuildings(
    const string& filePath, ostream& out) {

    LoadSummary summary;
    ifstream file(filePath.c_str());

    if (!file.is_open()) {
        out << "Error: cannot open " << filePath << '\n';
    } else {
        string line;
        size_t lineNumber = 0;

        while (getline(file, line)) {
            ++lineNumber;

            if (skipLine(line)) continue;

            const vector<string> fields = split(line, '|');
            string error;

            if (fields.size() != 1) {
                error = "expected 1 field, got " +
                        to_string(fields.size());
            } else if (addBuilding(fields[0], &error)) {
                ++summary.accepted;
                continue;
            }

            ++summary.rejected;

            out << "Warning: " << filePath
                << ": line " << lineNumber
                << ": " << error << '\n';
        }
    }

    out << filePath << ": " << summary.accepted
        << " accepted, " << summary.rejected
        << " rejected\n";

    return summary;
}

// Loads connections from a file
CampusGraph::LoadSummary CampusGraph::loadConnections(
    const string& filePath, ostream& out) {

    LoadSummary summary;
    ifstream file(filePath.c_str());

    if (!file.is_open()) {
        out << "Error: cannot open " << filePath << '\n';
    } else {
        string line;
        size_t lineNumber = 0;

        while (getline(file, line)) {
            ++lineNumber;

            if (skipLine(line)) continue;

            const vector<string> fields = split(line, '|');
            string error;

            if (fields.size() != 2) {
                error = "expected 2 fields, got " +
                        to_string(fields.size());
            } else if (addConnection(
                           fields[0], fields[1], &error)) {
                ++summary.accepted;
                continue;
            }

            ++summary.rejected;

            out << "Warning: " << filePath
                << ": line " << lineNumber
                << ": " << error << '\n';
        }
    }

    out << filePath << ": " << summary.accepted
        << " accepted, " << summary.rejected
        << " rejected\n";

    return summary;
}

// Finds the original building name
bool CampusGraph::findBuilding(
    const string& name,
    string& canonicalName) const {

    const int index = buildingIndex(name);

    if (index < 0) return false;

    canonicalName = buildings[static_cast<size_t>(index)].name;
    return true;
}

// Displays the campus graph
void CampusGraph::displayGraph(ostream& out) const {
    if (buildings.empty()) {
        out << "No buildings are loaded.\n";
        return;
    }

    out << "Campus graph:\n";

    for (size_t i = 0; i < buildings.size(); ++i) {
        out << buildings[i].name << ": ";

        if (buildings[i].neighbors.empty()) {
            out << "(no connections)";
        } else {
            for (size_t j = 0;
                 j < buildings[i].neighbors.size(); ++j) {

                if (j != 0) out << ", ";

                out << buildings[
                    buildings[i].neighbors[j]].name;
            }
        }

        out << '\n';
    }
}

// Displays building counts and degrees
void CampusGraph::displayCountsAndDegrees(
    ostream& out) const {

    out << "Total buildings: "
        << buildings.size() << '\n';

    out << "Total connections: "
        << connectionCount << '\n';

    if (buildings.empty()) {
        out << "No buildings are loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); ++i) {
        out << buildings[i].name
            << ": degree "
            << buildings[i].neighbors.size() << '\n';
    }
}

// Finds reachable buildings using BFS
bool CampusGraph::displayReachable(
    const string& start, ostream& out) const {

    const string input = trim(start);

    if (input.empty()) {
        out << "Error: starting building cannot be blank.\n";
        return false;
    }

    const int initial = buildingIndex(input);

    if (initial < 0) {
        out << "Error: unknown starting building: "
            << input << '\n';
        return false;
    }

    vector<bool> visited(buildings.size(), false);
    vector<size_t> distance(buildings.size(), 0);
    queue<size_t> frontier;

    const size_t startIndex = static_cast<size_t>(initial);

    visited[startIndex] = true;
    frontier.push(startIndex);

    size_t reachable = 0;

    out << "Reachable buildings from "
        << buildings[startIndex].name << ":\n";

    while (!frontier.empty()) {
        const size_t current = frontier.front();
        frontier.pop();

        ++reachable;

        out << buildings[current].name
            << " (distance " << distance[current] << ")\n";

        for (size_t neighbor : buildings[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                frontier.push(neighbor);
            }
        }
    }

    out << "Reachable: " << reachable
        << " of " << buildings.size()
        << " buildings\n";

    return true;
}

// Finds the shortest path using BFS
bool CampusGraph::displayShortestPath(
    const string& start,
    const string& destination,
    ostream& out) const {

    const string startName = trim(start);
    const string destName = trim(destination);

    if (startName.empty() || destName.empty()) {
        out << "Error: building name cannot be blank.\n";
        return false;
    }

    const int startIndex = buildingIndex(startName);
    const int destIndex = buildingIndex(destName);

    if (startIndex < 0) {
        out << "Error: unknown starting building: "
            << startName << '\n';
        return false;
    }

    if (destIndex < 0) {
        out << "Error: unknown destination building: "
            << destName << '\n';
        return false;
    }

    const size_t source = static_cast<size_t>(startIndex);
    const size_t target = static_cast<size_t>(destIndex);

    vector<bool> visited(buildings.size(), false);
    vector<int> parent(buildings.size(), -1);
    queue<size_t> frontier;

    visited[source] = true;
    frontier.push(source);

    while (!frontier.empty() && !visited[target]) {
        const size_t current = frontier.front();
        frontier.pop();

        for (size_t neighbor : buildings[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = static_cast<int>(current);
                frontier.push(neighbor);
            }
        }
    }

    if (!visited[target]) {
        out << "No path exists from "
            << buildings[source].name << " to "
            << buildings[target].name << ".\n";
        return false;
    }

    vector<size_t> path;

    for (int current = destIndex; current >= 0;
         current = parent[static_cast<size_t>(current)]) {
        path.push_back(static_cast<size_t>(current));
    }

    reverse(path.begin(), path.end());

    out << "Shortest path:\n";

    for (size_t index : path) {
        out << buildings[index].name << '\n';
    }

    out << "Number of connections: "
        << path.size() - 1 << '\n';

    return true;
}

// Counts connected components
size_t CampusGraph::getComponentCount() const {
    vector<bool> visited(buildings.size(), false);
    queue<size_t> frontier;
    size_t components = 0;

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (visited[i]) continue;

        ++components;
        visited[i] = true;
        frontier.push(i);

        while (!frontier.empty()) {
            const size_t current = frontier.front();
            frontier.pop();

            for (size_t neighbor : buildings[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    frontier.push(neighbor);
                }
            }
        }
    }

    return components;
}

// Displays graph connectivity
void CampusGraph::displayConnectivityReport(
    ostream& out) const {

    out << "Total buildings: "
        << buildings.size() << '\n';

    out << "Total connections: "
        << connectionCount << '\n';

    if (buildings.empty()) {
        out << "No buildings are loaded.\n";
        out << "Highest degree: N/A\n";
        out << "Isolated buildings: None\n";
        out << "Connected components: 0\n";
        return;
    }

    size_t maxDegree = 0;

    for (const Building& building : buildings) {
        maxDegree = max(maxDegree,
                        building.neighbors.size());
    }

    out << "Highest degree (" << maxDegree << "): ";

    bool first = true;

    for (const Building& building : buildings) {
        if (building.neighbors.size() == maxDegree) {
            if (!first) out << ", ";
            out << building.name;
            first = false;
        }
    }

    out << '\n';
    out << "Isolated buildings: ";

    first = true;

    for (const Building& building : buildings) {
        if (building.neighbors.empty()) {
            if (!first) out << ", ";
            out << building.name;
            first = false;
        }
    }

    if (first) out << "None";

    out << "\nConnected components: "
        << getComponentCount() << '\n';
}

// Returns building and connection totals
size_t CampusGraph::getBuildingCount() const {
    return buildings.size();
}

size_t CampusGraph::getConnectionCount() const {
    return connectionCount;
}
