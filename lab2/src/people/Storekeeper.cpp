#include "lab2/people/Storekeeper.hpp"
#include <iostream>

Storekeeper::Storekeeper(std::string name, int id, double salary, std::string shift)
    : Employee(name, id, salary), shift_(shift) {}

void Storekeeper::work() { std::cout << getName() << " принимает товар в смену " << shift_ << "\n"; }
