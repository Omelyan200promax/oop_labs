#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class InvalidBookDataException : public WarehouseException
{
public:
    explicit InvalidBookDataException(const std::string &message) : WarehouseException(message) {}
};
