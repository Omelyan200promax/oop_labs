#pragma once
#include "lab2/orders/ReturnRequest.hpp"
#include "lab2/common/Price.hpp"

class Refund
{
private:
    ReturnRequest request_;
    Price amount_;

public:
    Refund(ReturnRequest request, Price amount);
    void processRefund();
};
