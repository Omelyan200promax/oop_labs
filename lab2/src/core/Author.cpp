#include "lab2/core/Author.hpp"

Author::Author(std::string firstName, std::string lastName, std::string country, int birthYear, int deathYear)
    : firstName_(firstName), lastName_(lastName), country_(country), birthYear_(birthYear), deathYear_(deathYear) {}

std::string Author::getFullName() const { return firstName_ + " " + lastName_; }
int Author::getBirthYear() const { return birthYear_; }
int Author::getDeathYear() const { return deathYear_; }
