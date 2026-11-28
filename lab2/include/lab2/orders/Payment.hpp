/**
 * @file Payment.hpp
 * @brief Класс Payment — оплата заказа.
 */
#pragma once
#include "lab2/people/Customer.hpp"
#include "lab2/common/Price.hpp"

/**
 * @brief Платёж клиента.
 * @details Работает с копией клиента, поэтому проверяет достаточность средств, но баланс настоящего клиента сам не уменьшает.
 */
class Payment
{
private:
    int id_; /**< Номер платежа. */
    Customer customer_; /**< Плательщик (копия). */
    Price amount_; /**< Сумма платежа. */
    bool isSuccess_; /**< Признак успешной оплаты. */

public:
    /**
     * @brief Создаёт платёж.
     * @param id Номер платежа.
     * @param customer Плательщик.
     * @param amount Сумма.
     */
    Payment(int id, Customer customer, Price amount);
    /**
     * @brief Проводит платёж: списывает сумму с баланса (копии) клиента.
     * @throws InvalidPaymentException Если на балансе недостаточно средств.
     */
    void processPayment();
    /**
     * @brief Результат платежа.
     * @return true, если платёж прошёл.
     */
    bool getStatus() const;
};
