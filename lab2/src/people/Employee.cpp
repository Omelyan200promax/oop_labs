#include "lab2/people/Employee.hpp"
#include <iostream>

Employee::Employee(std::string name, int id, double salary) : name_(name), id_(id), salary_(salary) {}
std::string Employee::getName() const { return name_; }
void Employee::work() { std::cout << name_ << " выполняет базовую работу\n"; }
