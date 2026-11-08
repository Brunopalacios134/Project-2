#include "DepartmentNode.h"

DepartmentNode::DepartmentNode(const string& departmentName)
{
    name = departmentName;
    parent = nullptr;
}