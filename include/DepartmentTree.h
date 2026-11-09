#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include "DepartmentNode.h"

using namespace std;

class DepartmentTree
{
private:
    DepartmentNode* root;
    // searches for a department
    DepartmentNode* searchHelper(
        DepartmentNode* node,
        const string& name);
    // displays hierarchy with indentation
    void displayHierarchyHelper(
        DepartmentNode* node,
        int depth);
    // Visits departments in preorder
    void preorderHelper(
        DepartmentNode* node);
    // Frees all nodes in the tree
    void destroyTree(
        DepartmentNode* node);
    // Calculates the depth of a department
    int calculateDepth(
        DepartmentNode* node);

public:
    DepartmentTree();
    ~DepartmentTree();
    // Checks if the tree is empty
    bool isEmpty() const;
    // Adds a department to the tree
    bool addDepartment(
        const string& departmentName,
        const string& parentName = "");
    // Searches for a department by name
    DepartmentNode* search(
        const string& departmentName);
    // Displays information about a department
    void displayDepartmentInfo(
        const string& departmentName);
    // Displays the complete department hierarchy
    void displayHierarchy();
    // Displays all departments in preorder
    void preorderTraversal();
    // Loads departments from a file
    void loadFromFile(const string& filename);
    // Returns the root of the tree
    DepartmentNode* getRoot() const;
};

#endif