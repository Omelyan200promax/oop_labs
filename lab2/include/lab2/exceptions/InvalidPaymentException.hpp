/**
 * @file InvalidPaymentException.hpp
 * @brief Исключение InvalidPaymentException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Ошибка оплаты (например, недостаточно средств).
 * @details Наследуется от WarehouseException.
 */
class InvalidPaymentException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit InvalidPaymentException(const std::string &message) : WarehouseException(message) {}
};
