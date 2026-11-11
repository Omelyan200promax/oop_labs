#pragma once
#include "lab2/people/Employee.hpp"
#include <string>

class Translator : public Employee
{
private:
    std::string languagePair_;

public:
    Translator(std::string name, int id, double salary, std::string languagePair);
    void translate();
};
