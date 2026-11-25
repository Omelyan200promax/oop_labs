#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class InvalidOrderException : public WarehouseException
{
public:
    explicit InvalidOrderException(const std::string &message) : WarehouseException(message) {}
};
