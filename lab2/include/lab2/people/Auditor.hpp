#pragma once
#include "lab2/people/Employee.hpp"

class Auditor : public Employee
{
public:
    Auditor(std::string name, int id, double salary, Role role);
    void work() override;
    void checkInventory();
};