#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class InvalidPaymentException : public WarehouseException
{
public:
    explicit InvalidPaymentException(const std::string &message) : WarehouseException(message) {}
};
