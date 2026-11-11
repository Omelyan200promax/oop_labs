#pragma once
#include <string>

class Author
{
private:
    std::string firstName_;
    std::string lastName_;
    std::string country_;

public:
    Author(std::string firstName, std::string lastName, std::string country);
    std::string getFullName() const;
};
