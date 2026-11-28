/**
 * @file Discount.hpp
 * @brief Класс Discount — скидка.
 */
#pragma once
#include <string>
/**
 * @brief Именованная процентная скидка.
 */
class Discount
{
private:
    std::string name_; /**< Название скидки. */
    double percent_; /**< Размер скидки, %. */

public:
    /**
     * @brief Создаёт скидку.
     * @param name Название.
     * @param percent Размер в процентах.
     */
    Discount(std::string name, double percent);
    /**
     * @brief Применяет скидку к цене.
     * @details Саму цену не меняет, а возвращает новое значение.
     * @param price Исходная цена.
     * @return Цена после скидки.
     */
    double apply(double price) const;
};
