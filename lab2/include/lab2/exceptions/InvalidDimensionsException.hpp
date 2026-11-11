#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class InvalidDimensionsException : public WarehouseException
{
public:
    explicit InvalidDimensionsException(const std::string &message) : WarehouseException(message) {}
};
