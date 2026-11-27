#include "lab2/people/Storekeeper.hpp"
#include <iostream>

Storekeeper::Storekeeper(std::string name, int id, double salary, Role role, std::string shift)
    : Employee(name, id, salary, role), shift_(shift) {}
void Storekeeper::work() { std::cout << getName() << " принимает товар в смену \"" << shift_ << "\"\n"; }
void Storekeeper::sortBooks() { std::cout << getName() << " раскладывает книги по коробкам и полкам.\n"; }
