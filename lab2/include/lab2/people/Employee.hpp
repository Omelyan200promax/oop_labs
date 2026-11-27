#pragma once
#include <string>
#include "lab2/people/Role.hpp"

class Employee
{
protected:
    std::string name_;
    int id_;
    double salary_;
    Role role_;

public:
    Employee(std::string name, int id, double salary, Role role);
    std::string getName() const;
    double getSalary() const;
    Role getRole() const;
    virtual void work();
};