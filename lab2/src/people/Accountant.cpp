// cpp
#include "lab2/people/Accountant.hpp"
#include <iostream>

Accountant::Accountant(std::string name, int id, double salary, Role role, std::string taxId)
    : Employee(name, id, salary, role), taxId_(taxId) {}
void Accountant::work() { std::cout << getName() << " начисляет зарплату.\n"; }
void Accountant::calculateSalary(Employee &emp)
{
    std::cout << "Начислена зарплата " << emp.getSalary() << " BYN сотруднику " << emp.getName() << ".\n";
}
