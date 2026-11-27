#pragma once
#include "lab2/people/Employee.hpp"

class Editor : public Employee
{
private:
    int experienceYears_;

public:
    Editor(std::string name, int id, double salary, Role role, int experienceYears);
    void work() override;
    void editBook();
};
