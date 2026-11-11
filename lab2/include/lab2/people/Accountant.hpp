#pragma once
#include "lab2/people/Employee.hpp"
#include <string>

class Accountant : public Employee
{
private:
    std::string taxId_;

public:
    Accountant(std::string name, int id, double salary, std::string taxId);
    void calculateSalary();
};
