/**
 * @file DeliveryFailedException.hpp
 * @brief Исключение DeliveryFailedException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Ошибка доставки (например, доставка не была начата или транспорт неисправен).
 * @details Наследуется от WarehouseException.
 */
class DeliveryFailedException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit DeliveryFailedException(const std::string &message) : WarehouseException(message) {}
};
