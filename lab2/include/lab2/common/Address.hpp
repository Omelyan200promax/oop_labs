/**
 * @file Address.hpp
 * @brief Класс Address — адрес (город и улица).
 */
#pragma once
#include <string>

/**
 * @brief Почтовый адрес клиента, склада или поставщика.
 * @details Хранит город и улицу; полный адрес собирается в виде «город, улица».
 */
class Address
{
private:
    std::string city_; /**< Город. */
    std::string street_; /**< Улица и дом. */

public:
    /**
     * @brief Создаёт адрес.
     * @param city Город.
     * @param street Улица и дом.
     */
    Address(std::string city, std::string street);
    /**
     * @brief Возвращает адрес одной строкой.
     * @return Строка вида «город, улица».
     */
    std::string getFullAddress() const;
};
