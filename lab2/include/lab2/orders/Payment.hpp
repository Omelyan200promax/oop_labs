#pragma once
#include "lab2/people/Customer.hpp"
#include "lab2/common/Price.hpp"

class Payment
{
private:
    int id_;
    Customer customer_;
    Price amount_;
    bool isSuccess_;

public:
    Payment(int id, Customer customer, Price amount);
    void processPayment();
    bool getStatus() const;
};
