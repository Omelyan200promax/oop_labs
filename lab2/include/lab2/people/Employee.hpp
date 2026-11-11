#pragma once
#include <string>

class Employee
{
protected:
    std::string name_;
    int id_;
    double salary_;

public:
    Employee(std::string name, int id, double salary);
    std::string getName() const;
    virtual void work(); // Виртуальный метод, чтобы наследники могли его переопределить
};
