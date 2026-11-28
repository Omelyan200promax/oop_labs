/**
 * @file SupplierNotFoundException.hpp
 * @brief Исключение SupplierNotFoundException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Поставщик не найден или нет действующего договора с ним.
 * @details Наследуется от WarehouseException.
 */
class SupplierNotFoundException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit SupplierNotFoundException(const std::string &message) : WarehouseException(message) {}
};
