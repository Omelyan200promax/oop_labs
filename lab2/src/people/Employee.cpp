#include "lab2/people/Employee.hpp"
#include <iostream>

Employee::Employee(std::string name, int id, double salary, Role role)
    : name_(name), id_(id), salary_(salary), role_(role) {}
std::string Employee::getName() const { return name_; }
double Employee::getSalary() const { return salary_; }
Role Employee::getRole() const { return role_; }
void Employee::work() { std::cout << name_ << " выполняет базовую работу\n"; }