/**
 * @file CapacityExceededException.hpp
 * @brief Исключение CapacityExceededException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Превышена вместимость (полки, секции или склада).
 * @details Наследуется от WarehouseException.
 */
class CapacityExceededException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit CapacityExceededException(const std::string &message) : WarehouseException(message) {}
};
