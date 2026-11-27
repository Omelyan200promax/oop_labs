#include "lab2/people/Courier.hpp"
#include <iostream>

Courier::Courier(std::string name, int id, double salary, Role role, std::string vehicle)
    : Employee(name, id, salary, role), vehicle_(vehicle) {}
void Courier::work() { std::cout << getName() << " доставляет заказы на \"" << vehicle_ << "\"\n"; }
void Courier::deliverOrder() { std::cout << getName() << " отправился доставлять заказ.\n"; }