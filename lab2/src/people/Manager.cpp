#include "lab2/people/Manager.hpp"
#include <iostream>

Manager::Manager(std::string name, int id, double salary, Role role, std::string department)
    : Employee(name, id, salary, role), department_(department) {}
void Manager::work() { std::cout << getName() << " управляет отделом \"" << department_ << "\"\n"; }
void Manager::createReport() { std::cout << getName() << " формирует отчет по продажам.\n"; }
void Manager::applyDiscountToBook() { std::cout << getName() << " применяет скидку к книге.\n"; }
