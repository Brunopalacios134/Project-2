#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include "DepartmentNode.h"

using namespace std;

class DepartmentTree
{
private:
    DepartmentNode* root;

    DepartmentNode* searchHelper(
        DepartmentNode* node,
        const string& name);

    void displayHierarchyHelper(
        DepartmentNode* node,
        int depth);

    void preorderHelper(
        DepartmentNode* node);

    void destroyTree(
        DepartmentNode* node);

    int calculateDepth(
        DepartmentNode* node);

public:
    DepartmentTree();
    ~DepartmentTree();

    bool isEmpty() const;

    bool addDepartment(
        const string& departmentName,
        const string& parentName = "");

    DepartmentNode* search(
        const string& departmentName);

    void displayDepartmentInfo(
        const string& departmentName);

    void displayHierarchy();

    void preorderTraversal();
    
    void loadFromFile(const string& filename);

    DepartmentNode* getRoot() const;
};

#endif