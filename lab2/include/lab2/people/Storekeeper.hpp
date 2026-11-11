#pragma once
#include "lab2/people/Employee.hpp"

class Storekeeper : public Employee
{
private:
    std::string shift_;

public:
    Storekeeper(std::string name, int id, double salary, std::string shift);
    void work() override;
};
