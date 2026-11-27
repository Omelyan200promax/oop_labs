#pragma once
#include "lab2/people/Employee.hpp"

class Accountant : public Employee
{
private:
    std::string taxId_;

public:
    Accountant(std::string name, int id, double salary, Role role, std::string taxId);
    void work() override;
    void calculateSalary(Employee &emp);
};
