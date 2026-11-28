/**
 * @file InventoryMismatchException.hpp
 * @brief Исключение InventoryMismatchException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Результаты инвентаризации не совпадают с данными учёта.
 * @details Наследуется от WarehouseException.
 */
class InventoryMismatchException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit InventoryMismatchException(const std::string &message) : WarehouseException(message) {}
};
