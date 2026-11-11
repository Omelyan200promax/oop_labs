#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"

class Supplier
{
private:
    std::string companyName_;
    ContactInfo contact_;

public:
    Supplier(std::string companyName, ContactInfo contact);
    void sendSupply();
};
