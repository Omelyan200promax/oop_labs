/**
 * @file AccessDeniedException.hpp
 * @brief Исключение AccessDeniedException.
 */
#pragma once
#include "lab2/exceptions/WarehouseException.hpp"

/**
 * @brief Доступ запрещён: уровень доступа пользователя ниже требуемого.
 * @details Наследуется от WarehouseException.
 */
class AccessDeniedException : public WarehouseException
{
public:
    /**
     * @brief Создаёт исключение.
     * @param message Текст ошибки.
     */
    explicit AccessDeniedException(const std::string &message) : WarehouseException(message) {}
};
