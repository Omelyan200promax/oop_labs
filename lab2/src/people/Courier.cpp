#include "lab2/people/Courier.hpp"
#include <iostream>

Courier::Courier(std::string name, int id, double salary, std::string vehicle)
    : Employee(name, id, salary), vehicle_(vehicle) {}

void Courier::work() { std::cout << getName() << " доставляет заказы на " << vehicle_ << "\n"; }
