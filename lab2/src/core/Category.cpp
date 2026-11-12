#include "lab2/core/Category.hpp"

Category::Category(std::string name, std::string description) : name_(name), description_(description) {}
std::string Category::getName() const { return name_; }
