#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class OutOfStockException : public WarehouseException
{
public:
    explicit OutOfStockException(const std::string &message) : WarehouseException(message) {}
};
