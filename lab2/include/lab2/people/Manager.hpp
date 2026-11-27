#pragma once
#include "lab2/people/Employee.hpp"

class Manager : public Employee
{
private:
    std::string department_;

public:
    Manager(std::string name, int id, double salary, Role role, std::string department);
    void work() override;
    void createReport();
    void applyDiscountToBook();
};
