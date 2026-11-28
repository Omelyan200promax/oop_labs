/**
 * @file Price.hpp
 * @brief Класс Price — цена с валютой.
 */
#pragma once
#include <string>
/**
 * @brief Денежная сумма с указанием валюты.
 */
class Price
{
private:
    double amount_; /**< Сумма. */
    std::string currency_; /**< Код валюты (например, BYN). */

public:
    /**
     * @brief Создаёт цену.
     * @param amount Сумма.
     * @param currency Валюта.
     * @throws std::invalid_argument Если сумма отрицательна.
     */
    Price(double amount, std::string currency);
    /**
     * @brief Уменьшает цену на процент.
     * @details Если процент не лежит в диапазоне (0; 100], цена не меняется.
     * @param percent Размер скидки, %.
     */
    void applyDiscount(double percent);
    /**
     * @brief Форматирует цену.
     * @return Строка вида «сумма валюта».
     */
    std::string toString() const;
    /**
     * @brief Возвращает сумму.
     * @return Числовое значение цены.
     */
    double getAmount() const;
};
