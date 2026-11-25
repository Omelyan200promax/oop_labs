#pragma once
#include "lab2/orders/Order.hpp"
#include "lab2/common/Address.hpp"

class Delivery
{
private:
    Order order_;
    Address address_;
    bool isDelivered_;

public:
    Delivery(Order order, Address address);
    void startDelivery();
    void completeDelivery();
    bool isDelivered() const;
};
