#include "lab2/people/Manager.hpp"
#include <iostream>

Manager::Manager(std::string name, int id, double salary, std::string department)
    : Employee(name, id, salary), department_(department) {}

void Manager::work() { std::cout << getName() << " управляет отделом " << department_ << "\n"; }
