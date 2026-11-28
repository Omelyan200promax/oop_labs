/**
 * @file InvalidDimensionsException.hpp
 * @brief Исключение InvalidDimensionsException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Некорректные габариты (размеры должны быть положительными).
 * @details Наследуется от WarehouseException.
 */
class InvalidDimensionsException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit InvalidDimensionsException(const std::string &message) : WarehouseException(message) {}
};
