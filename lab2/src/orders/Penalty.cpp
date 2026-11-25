#include "lab2/orders/Penalty.hpp"
#include <iostream>

Penalty::Penalty(std::string reason, Price amount) : reason_(reason), amount_(amount) {}
void Penalty::applyPenalty() { std::cout << "Штраф применен: " << reason_ << "\n"; }
