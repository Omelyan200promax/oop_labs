/**
 * @file WarehouseException.hpp
 * @brief Базовое исключение WarehouseException.
 */
#pragma once
#include <stdexcept>
#include <string>

/**
 * @brief Базовое исключение предметной области «книжный склад».
 * @details Наследуется от std::runtime_error; от него происходят все остальные исключения проекта.
 */
class WarehouseException : public std::runtime_error
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit WarehouseException(const std::string &message) : std::runtime_error(message) {}
};
