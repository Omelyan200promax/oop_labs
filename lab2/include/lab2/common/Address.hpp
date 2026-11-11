#pragma once
#include <string>

class Address
{
private:
    std::string city_;
    std::string street_;

public:
    Address(std::string city, std::string street);
    std::string getFullAddress() const;
};
