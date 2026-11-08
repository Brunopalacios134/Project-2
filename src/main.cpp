#include <iostream> 
#include <string>
#include <cctype>
#include <vector>
#include <stdexcept>
#include "Utils.h"
#include "FacilityDatabase.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"
using namespace std;
int readMenuChoice() {
    cout << "Enter choice: ";
    string line;
    if (!getline(cin, line)) {
        return 0;
    }
    line = trim(line);
    if (line.empty()) {
        return -1;
    }
    for (char c : line) {
        if (!isdigit((unsigned char)c)) {
            return -1;
        }
    }
    try {
        return stoi(line);
    } catch (const exception&) {
        return -1;
    }
}
void printMenu() {
    cout << endl;
    cout << "====== Smart Campus Menu ======" << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" << endl;
    cout << "4. Display graph counts and degrees" << endl;
    cout << "5. Find reachable buildings (BFS)" << endl;
    cout << "6. Add department" << endl;
    cout << "7. Search department" << endl;
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "0. Exit" << endl;
}
int main(int argc, char* argv[]) {
    string dataDir = "data";
    if (argc > 1) {
        dataDir = argv[1];
    }
    CampusGraph graph;
    graph.loadBuildings(dataDir + "/buildings.txt");
    graph.loadConnections(dataDir + "/connections.txt");
    vector<string> buildings = graph.getBuildingNames();
    FacilityDatabase db;
    db.loadFromFile(dataDir + "/facilities.txt", buildings);
    DepartmentTree tree;
    tree.loadFromFile(dataDir + "/departments.txt");
    while (true) {
        printMenu();
        int choice = readMenuChoice();
        if (choice == 0) {
            cout << "Goodbye." << endl;
            break;
        }
        else if (choice == 1) {
            db.displayAll();
        }
        else if (choice == 2) {
            cout << "Enter facility ID: ";
            string input;
            getline(cin, input);
            db.searchById(input);
        }
        else if (choice == 3) {
            graph.displayGraph();
        }
        else if (choice == 4) {
            graph.displayCountsAndDegrees();
        }
        else if (choice == 5) {
            cout << "Enter starting building: ";
            string name;
            getline(cin, name);
            graph.displayReachable(name);
        }
        else if (choice == 6) {
            cout << "Enter department name: ";

            string name;
            getline(cin, name);
            name = trim(name);

            if (name.empty()) {
                cout << "Error: department name cannot be blank." << endl;
            }
            else if (tree.isEmpty()) {
                tree.addDepartment(name);
            }
            else {
                cout << "Enter parent department: ";

                string parent;
                getline(cin, parent);
                parent = trim(parent);

                if (parent.empty()) {
                    cout << "Error: parent name cannot be blank." << endl;
                }
                else {
                    tree.addDepartment(name, parent);
                }
            }
        }
        else if (choice == 7) {
            cout << "Enter department name: ";

            string name;
            getline(cin, name);
            name = trim(name);

            if (name.empty()) {
                cout << "Error: department name cannot be blank." << endl;
            }
            else {
                tree.displayDepartmentInfo(name);
            }
        }
        else if (choice == 8) {
            tree.displayHierarchy();
        }
        else if (choice == 9) {
            tree.preorderTraversal();
        }

        else {
            cout << "Invalid choice. Please enter a number from 0 to 9." << endl;
        }
    }
    return 0;
}