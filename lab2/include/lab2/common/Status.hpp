/**
 * @file Status.hpp
 * @brief Класс Status — именованный статус.
 */
#pragma once
#include <string>
/**
 * @brief Именованный статус (например, статус заказа или оборудования).
 */
class Status
{
private:
    std::string name_; /**< Название статуса. */

public:
    /**
     * @brief Создаёт статус.
     * @param name Название.
     */
    Status(std::string name);
    /**
     * @brief Возвращает название статуса.
     * @return Название.
     */
    std::string getName() const;
};
