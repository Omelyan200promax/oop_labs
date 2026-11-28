/**
 * @file InvalidOrderException.hpp
 * @brief Исключение InvalidOrderException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Некорректное состояние заказа или запроса (например, возврат не одобрен).
 * @details Наследуется от WarehouseException.
 */
class InvalidOrderException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit InvalidOrderException(const std::string &message) : WarehouseException(message) {}
};
