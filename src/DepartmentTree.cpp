#include "DepartmentTree.h"
#include <iostream>
#include <algorithm>
#include "Utils.h"
#include <fstream>

using namespace std;

DepartmentTree::DepartmentTree()
{
    root = nullptr;
}

DepartmentTree::~DepartmentTree()
{
    destroyTree(root);
}
// Checks if the tree is empty
bool DepartmentTree::isEmpty() const
{
    return root == nullptr;
}

DepartmentNode* DepartmentTree::getRoot() const
{
    return root;
}

DepartmentNode* DepartmentTree::searchHelper(
    DepartmentNode* node,
    const string& name)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    string nodeName = node->name;
    string targetName = name;

    transform(
        nodeName.begin(),
        nodeName.end(),
        nodeName.begin(),
        ::tolower);

    transform(
        targetName.begin(),
        targetName.end(),
        targetName.begin(),
        ::tolower);

    if (nodeName == targetName)
    {
        return node;
    }

    for (DepartmentNode* child : node->children)
    {
        DepartmentNode* result =
            searchHelper(child, name);

        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr;
}
// Searches for a department by name
DepartmentNode* DepartmentTree::search(
    const string& departmentName)
{
    return searchHelper(root, departmentName);
}
// Adds a department to the tree
bool DepartmentTree::addDepartment(
    const string& departmentName,
    const string& parentName)
{
    if (departmentName.empty())
    {
        cout << "Department name cannot be empty.\n";
        return false;
    }

    if (search(departmentName) != nullptr)
    {
        cout << "Duplicate department name.\n";
        return false;
    }

    if (root == nullptr)
    {
        root = new DepartmentNode(departmentName);

        cout << "Root department created: "
             << departmentName << endl;

        return true;
    }

    DepartmentNode* parent =
        search(parentName);

    if (parent == nullptr)
    {
        cout << "Parent department not found.\n";
        return false;
    }

    DepartmentNode* newNode =
        new DepartmentNode(departmentName);

    newNode->parent = parent;

    parent->children.push_back(newNode);

    cout << departmentName
         << " added under "
         << parentName
         << endl;

    return true;
}
// Calculates the depth of a department
int DepartmentTree::calculateDepth(
    DepartmentNode* node)
{
    int depth = 0;

    while (node != nullptr &&
           node->parent != nullptr)
    {
        depth++;
        node = node->parent;
    }

    return depth;
}

void DepartmentTree::displayDepartmentInfo(
    const string& departmentName)
{
    DepartmentNode* node =
        search(departmentName);

    if (node == nullptr)
    {
        cout << "Department not found.\n";
        return;
    }

    cout << "\nDepartment Information\n";
    cout << "----------------------\n";

    cout << "Name: "
         << node->name
         << endl;

    if (node->parent == nullptr)
    {
        cout << "Parent: None\n";
    }
    else
    {
        cout << "Parent: "
             << node->parent->name
             << endl;
    }

    cout << "Direct Children: "
         << node->children.size()
         << endl;

    cout << "Depth: "
         << calculateDepth(node)
         << endl;
}

void DepartmentTree::displayHierarchyHelper(
    DepartmentNode* node,
    int depth)
{
    if (node == nullptr)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        cout << "    ";
    }

    cout << node->name << endl;

    for (DepartmentNode* child :
         node->children)
    {
        displayHierarchyHelper(
            child,
            depth + 1);
    }
}

void DepartmentTree::displayHierarchy()
{
    if (root == nullptr)
    {
        cout << "No departments loaded.\n";
        return;
    }

    displayHierarchyHelper(root, 0);
}

void DepartmentTree::preorderHelper(
    DepartmentNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    cout << node->name << endl;

    for (DepartmentNode* child :
         node->children)
    {
        preorderHelper(child);
    }
}

void DepartmentTree::preorderTraversal()
{
    if (root == nullptr)
    {
        cout << "No departments loaded.\n";
        return;
    }

    preorderHelper(root);
}

void DepartmentTree::destroyTree(
    DepartmentNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    for (DepartmentNode* child :
         node->children)
    {
        destroyTree(child);
    }

    delete node;
}
void DepartmentTree::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: cannot open file " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected" << endl;
        return;
    }
    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;
    while (getline(file, line)) {
        lineNumber++;
        string clean = trim(line);
        if (clean.empty() || clean[0] == '#') {
            continue;
        }
        vector<string> parts = split(clean, '|');
        if (parts.size() != 2) {
            cout << "Warning: " << filename << ", line " << lineNumber << ": expected 2 fields, found " << parts.size() << endl;
            rejected++;
            continue;
        }
        string name = trim(parts[0]);
        string parentName = trim(parts[1]);

        if (name.empty() || parentName.empty()) {
            cout << "Warning: " << filename << ", line " << lineNumber << ": empty required field" << endl;
            rejected++;
            continue;
        }

        if (isEmpty()) {
            if (toUpper(parentName) != "NONE") {
                cout << "Warning: " << filename << ", line " << lineNumber << ": first department must have parent NONE" << endl;
                rejected++;
                continue;
            }
        } else {
            if (search(name) != nullptr) {
                cout << "Warning: " << filename << ", line " << lineNumber << ": duplicate department " << name << endl;
                rejected++;
                continue;
            }

            if (search(parentName) == nullptr) {
                cout << "Warning: " << filename << ", line " << lineNumber << ": unknown parent " << parentName << endl;
                rejected++;
                continue;
            }
        }

        addDepartment(name, parentName);
        accepted++;
    }

    cout << filename << ": " << accepted << " accepted, "
         << rejected << " rejected" << endl;
}