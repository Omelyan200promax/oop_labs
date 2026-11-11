#include "lab2/people/Customer.hpp"

Customer::Customer(std::string name, ContactInfo contact, Address address, double balance)
    : name_(name), contact_(contact), address_(address), balance_(balance) {}

bool Customer::pay(double amount)
{
    if (balance_ >= amount)
    {
        balance_ -= amount;
        return true;
    }
    return false;
}
