#include "lab2/common/Discount.hpp"
Discount::Discount(std::string name, double percent) : name_(name), percent_(percent) {}
double Discount::apply(double price) const { return price - (price * percent_ / 100.0); }
