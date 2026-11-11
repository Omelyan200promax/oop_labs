#pragma once
#include <string>

class ContactInfo
{
private:
    std::string phone_;
    std::string email_;

public:
    ContactInfo(std::string phone, std::string email);
    std::string getEmail() const;
};
