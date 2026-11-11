#include "lab2/people/Accountant.hpp"
#include <iostream>

Accountant::Accountant(std::string name, int id, double salary, std::string taxId)
    : Employee(name, id, salary), taxId_(taxId) {}

void Accountant::calculateSalary()
{
    std::cout << getName() << " начисляет зарплату. ИНН: " << taxId_ << "\n";
}
