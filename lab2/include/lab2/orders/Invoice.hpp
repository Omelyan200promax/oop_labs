/**
 * @file Invoice.hpp
 * @brief Класс Invoice — счёт на оплату.
 */
#pragma once
#include "lab2/orders/Order.hpp"

/**
 * @brief Счёт на оплату заказа.
 */
class Invoice
{
private:
    int number_; /**< Номер счёта. */
    Order order_; /**< Заказ, по которому выставлен счёт. */
    double totalAmount_; /**< Сумма счёта (после generate()). */

public:
    /**
     * @brief Создаёт счёт с нулевой суммой.
     * @param number Номер счёта.
     * @param order Заказ.
     */
    Invoice(int number, Order order);
    /**
     * @brief Формирует счёт: рассчитывает сумму по составу заказа.
     */
    void generate();
    /**
     * @brief Сумма счёта.
     * @return Сумма в BYN; 0 до вызова generate().
     */
    double getAmount() const;
};
