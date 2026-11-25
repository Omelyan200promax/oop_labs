#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class BookNotFoundException : public WarehouseException
{
public:
    explicit BookNotFoundException(const std::string &message) : WarehouseException(message) {}
};
