#include "lab2/core/Author.hpp"

Author::Author(std::string firstName, std::string lastName, std::string country)
    : firstName_(firstName), lastName_(lastName), country_(country) {}

std::string Author::getFullName() const
{
    return firstName_ + " " + lastName_;
}
