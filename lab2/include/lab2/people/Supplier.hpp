#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"
#include "lab2/core/Book.hpp"

class Supplier
{
private:
    std::string companyName_;
    ContactInfo contact_;

public:
    Supplier(std::string companyName, ContactInfo contact);
    void supplyBooks(Book &book, int count);
};
