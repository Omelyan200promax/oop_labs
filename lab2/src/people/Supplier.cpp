#include "lab2/people/Supplier.hpp"
#include <iostream>

Supplier::Supplier(std::string companyName, ContactInfo contact)
    : companyName_(companyName), contact_(contact) {}

void Supplier::sendSupply() { std::cout << companyName_ << " отгружает книги на склад\n"; }
