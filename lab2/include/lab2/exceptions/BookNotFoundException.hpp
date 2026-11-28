/**
 * @file BookNotFoundException.hpp
 * @brief Исключение BookNotFoundException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Книга не найдена (например, по ISBN).
 * @details Наследуется от WarehouseException.
 */
class BookNotFoundException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit BookNotFoundException(const std::string &message) : WarehouseException(message) {}
};
