/**
 * @file ReturnRequest.hpp
 * @brief Класс ReturnRequest — запрос на возврат.
 */
#pragma once
#include "lab2/orders/Order.hpp"

/**
 * @brief Запрос клиента на возврат заказа.
 * @details Создаётся неодобренным; одобряет менеджер.
 */
class ReturnRequest
{
private:
    Order order_; /**< Заказ, по которому запрошен возврат (копия). */
    std::string reason_; /**< Причина возврата. */
    bool isApproved_; /**< Признак одобрения. */

public:
    /**
     * @brief Создаёт неодобренный запрос.
     * @param order Заказ.
     * @param reason Причина возврата.
     */
    ReturnRequest(Order order, std::string reason);
    /**
     * @brief Одобряет запрос.
     */
    void approve();
    /**
     * @brief Проверяет одобрение.
     * @return true, если запрос одобрен.
     */
    bool isApproved() const;
};
