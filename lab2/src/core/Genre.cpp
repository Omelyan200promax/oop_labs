#include "lab2/core/Genre.hpp"

Genre::Genre(std::string name, std::string description) : name_(name), description_(description) {}

std::string Genre::getDescription() const
{
    return name_ + ": " + description_;
}
