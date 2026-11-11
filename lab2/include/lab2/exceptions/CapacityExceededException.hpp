#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class CapacityExceededException : public WarehouseException
{
public:
    explicit CapacityExceededException(const std::string &message) : WarehouseException(message) {}
};
