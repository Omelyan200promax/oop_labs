#pragma once
#include "lab2/orders/Order.hpp"

class ReturnRequest
{
private:
    Order order_;
    std::string reason_;
    bool isApproved_;

public:
    ReturnRequest(Order order, std::string reason);
    void approve();
    bool isApproved() const;
};
