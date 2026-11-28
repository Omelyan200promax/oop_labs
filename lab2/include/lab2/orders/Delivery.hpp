/**
 * @file Delivery.hpp
 * @brief Класс Delivery — доставка заказа.
 */
#pragma once
#include "lab2/orders/Order.hpp"
#include "lab2/common/Address.hpp"

/**
 * @brief Доставка заказа курьером по адресу клиента.
 * @details Работает с копией заказа: статус реального заказа вызывающий код синхронизирует сам. Статусы: «In Delivery» после начала, «Delivered» после завершения.
 */
class Delivery
{
private:
    Order order_; /**< Доставляемый заказ (копия). */
    Address address_; /**< Адрес доставки. */
    bool isDelivered_; /**< Признак завершённой доставки. */

public:
    /**
     * @brief Создаёт доставку (ещё не начатую).
     * @param order Заказ.
     * @param address Адрес доставки.
     */
    Delivery(Order order, Address address);
    /**
     * @brief Начинает доставку.
     * @details Переводит заказ в статус «In Delivery».
     */
    void startDelivery();
    /**
     * @brief Завершает доставку.
     * @details Переводит заказ в статус «Delivered» и отмечает доставку выполненной.
     * @throws DeliveryFailedException Если доставка не была начата.
     */
    void completeDelivery();
    /**
     * @brief Проверяет, доставлен ли заказ.
     * @return true, если доставка завершена.
     */
    bool isDelivered() const;
};
