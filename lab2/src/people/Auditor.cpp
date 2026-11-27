#include "lab2/people/Auditor.hpp"
#include <iostream>

Auditor::Auditor(std::string name, int id, double salary, Role role)
    : Employee(name, id, salary, role) {}
void Auditor::work() { std::cout << getName() << " проводит аудит склада.\n"; }
void Auditor::checkInventory() { std::cout << getName() << " запускает проверку инвентаризации.\n"; }