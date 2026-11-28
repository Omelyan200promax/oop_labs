/**
 * @file ContactInfo.hpp
 * @brief Класс ContactInfo — контактные данные.
 */
#pragma once
#include <string>

/**
 * @brief Контактные данные: телефон и адрес электронной почты.
 */
class ContactInfo
{
private:
    std::string phone_; /**< Номер телефона. */
    std::string email_; /**< Адрес электронной почты. */

public:
    /**
     * @brief Создаёт контактные данные.
     * @param phone Телефон.
     * @param email Электронная почта.
     */
    ContactInfo(std::string phone, std::string email);
    /**
     * @brief Возвращает адрес электронной почты.
     * @return Email.
     */
    std::string getEmail() const;
};
