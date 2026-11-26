// Main program: loads the four data files in order.
// Author: Bruno Palacios Busnelli
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
// Reads and validates the user's menu choice
int readMenuChoice() {
    cout << "Enter choice: ";
    string line;
    // Exit if the input stream is closed
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
// Displays menu
void printMenu() {
    cout << endl;
    cout << "====== Smart Campus Menu ======" << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. Search facility by name" << endl;
    cout << "4. Search facility by category" << endl;
    cout << "5. View campus graph" << endl;
    cout << "6. Display graph counts and degrees" << endl;
    cout << "7. Find reachable buildings (BFS)" << endl;
    cout << "8. Find shortest path (BFS)" << endl;
    cout << "9. Add department" << endl;
    cout << "10. Search department" << endl;
    cout << "11. Display department hierarchy" << endl;
    cout << "12. Preorder traversal" << endl;
    cout << "13. Postorder traversal" << endl;
    cout << "14. Level-order traversal" << endl;
    cout << "15. Department statistics" << endl;
    cout << "16. Facility category report" << endl;
    cout << "17. Graph connectivity report" << endl;
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
        //0: Exit the program
        if (choice == 0) {
            cout << "Goodbye." << endl;
            break;
        }
        //1: Display all facilities
        else if (choice == 1) {
            db.displayAll();
        }
        //2: Search for a facility by ID
        else if (choice == 2) {
            cout << "Enter facility ID: ";
            string input;
            getline(cin, input);
            db.searchById(input);
        }
        //3: Search for facilities by name
        else if (choice == 3) {
            cout << "Enter facility name: ";
            string input;
            getline(cin, input);
            db.searchByName(input);
        }
        //4: Search for facilities by category
        else if (choice == 4) {
            cout << "Enter category: ";
            string input;
            getline(cin, input);
            db.searchByCategory(input);
        }
        //5: Display the campus graph
        else if (choice == 5) {
            graph.displayGraph();
        }
        //6: Display graph statistics
        else if (choice == 6) {
            graph.displayCountsAndDegrees();
        }
        //7: Find reachable buildings using BFS
        else if (choice == 7) {
            cout << "Enter starting building: ";
            string name;
            getline(cin, name);
            graph.displayReachable(name);
        }
        //8: Find the shortest path using BFS
        else if (choice == 8) {
            cout << "Enter starting building: ";
            string start;
            getline(cin, start);
            cout << "Enter destination building: ";
            string dest;
            getline(cin, dest);

            graph.displayShortestPath(start, dest);
        }
        //9: Add a new department
        else if (choice == 9) {
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
        //10: Search for a department
        else if (choice == 10) {
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
        //11: Display the department hierarchy
        else if (choice == 11) {
            tree.displayHierarchy();
        }
        //12: Display departments in preorder
        else if (choice == 12) {
            tree.preorderTraversal();
        }
        //13: Display departments in postorder
        else if (choice == 13) {
            cout << "Not implemented yet." << endl;
        }
        //14: Display departments in level order
        else if (choice == 14) {
            cout << "Not implemented yet." << endl;
        }
        //15: Display department statistics
        else if (choice == 15) {
            cout << "Not implemented yet." << endl;
        }
        //16: Display the facility category report
        else if (choice == 16) {
            db.displayCategoryReport();
        }
        //17: Display the graph connectivity report
        else if (choice == 17) {
            graph.displayConnectivityReport();
        }

        else {
            cout << "Invalid choice. Please enter a number from 0 to 17." << endl;
        }
    }
    return 0;
}