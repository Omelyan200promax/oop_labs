#pragma once
#include <string>

class Author
{
private:
    std::string firstName_;
    std::string lastName_;
    std::string country_;
    int birthYear_;
    int deathYear_; // 0, если жив
public:
    Author(std::string firstName, std::string lastName, std::string country, int birthYear = 1800, int deathYear = 0);
    std::string getFullName() const;
    int getBirthYear() const;
    int getDeathYear() const;
};
