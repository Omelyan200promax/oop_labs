#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class InventoryMismatchException : public WarehouseException
{
public:
    explicit InventoryMismatchException(const std::string &message) : WarehouseException(message) {}
};
