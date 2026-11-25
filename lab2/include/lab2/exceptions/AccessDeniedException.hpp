#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

class AccessDeniedException : public WarehouseException
{
public:
    explicit AccessDeniedException(const std::string &message) : WarehouseException(message) {}
};
