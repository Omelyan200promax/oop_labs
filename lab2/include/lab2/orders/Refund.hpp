/**
 * @file Refund.hpp
 * @brief Класс Refund — возврат денег.
 */
#pragma once
#include "lab2/orders/ReturnRequest.hpp"
#include "lab2/common/Price.hpp"

/**
 * @brief Возврат денег по одобренному запросу на возврат.
 * @details Сам баланс клиента не меняет — зачисление выполняет вызывающий код.
 */
class Refund
{
private:
    ReturnRequest request_; /**< Запрос на возврат. */
    Price amount_; /**< Возвращаемая сумма. */

public:
    /**
     * @brief Создаёт возврат.
     * @param request Запрос на возврат.
     * @param amount Сумма возврата.
     */
    Refund(ReturnRequest request, Price amount);
    /**
     * @brief Оформляет возврат.
     * @throws InvalidOrderException Если запрос на возврат не одобрен.
     */
    void processRefund();
    /**
     * @brief Сумма возврата.
     * @return Сумма.
     */
    double getAmount() const;
};
