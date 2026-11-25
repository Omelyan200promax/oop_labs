#pragma once
#include "lab2/orders/Order.hpp"

class Invoice
{
private:
    int number_;
    Order order_;
    double totalAmount_;

public:
    Invoice(int number, Order order);
    void generate();
    double getAmount() const;
};
