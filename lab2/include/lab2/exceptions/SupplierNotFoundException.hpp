#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class SupplierNotFoundException : public WarehouseException
{
public:
    explicit SupplierNotFoundException(const std::string &message) : WarehouseException(message) {}
};
