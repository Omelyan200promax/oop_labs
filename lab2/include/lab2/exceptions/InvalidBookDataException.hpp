/**
 * @file InvalidBookDataException.hpp
 * @brief Исключение InvalidBookDataException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Некорректные данные книги (пустое название или ISBN, дублирование ISBN).
 * @details Наследуется от WarehouseException.
 */
class InvalidBookDataException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit InvalidBookDataException(const std::string &message) : WarehouseException(message) {}
};
