#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"
#include "lab2/common/Address.hpp"

class Customer
{
private:
    std::string name_;
    ContactInfo contact_;
    Address address_;
    double balance_;

public:
    Customer(std::string name, ContactInfo contact, Address address, double balance);
    bool pay(double amount);
};
