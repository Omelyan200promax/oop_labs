#pragma once
#include "lab2/people/Employee.hpp"

class Courier : public Employee
{
private:
    std::string vehicle_;

public:
    Courier(std::string name, int id, double salary, std::string vehicle);
    void work() override;
};
