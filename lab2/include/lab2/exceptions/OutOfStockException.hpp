/**
 * @file OutOfStockException.hpp
 * @brief Исключение OutOfStockException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Книги нет в наличии в нужном количестве.
 * @details Наследуется от WarehouseException.
 */
class OutOfStockException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit OutOfStockException(const std::string &message) : WarehouseException(message) {}
};
