#include "lab2/core/Publisher.hpp"

Publisher::Publisher(std::string name, std::string city) : name_(name), city_(city) {}

std::string Publisher::getInfo() const
{
    return name_ + " (" + city_ + ")";
}
