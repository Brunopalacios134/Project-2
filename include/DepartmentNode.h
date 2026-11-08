#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

#include <string>
#include <vector>

using namespace std;

class DepartmentNode
{
public:
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;

    DepartmentNode(const string& departmentName);
};

#endif