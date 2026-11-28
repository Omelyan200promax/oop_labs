/**
 * @file Shipment.hpp
 * @brief Класс Shipment — отгрузка заказа со склада.
 */
#pragma once
#include "lab2/orders/Order.hpp"
#include "lab2/warehouse/Warehouse.hpp"

/**
 * @brief Отгрузка заказа со склада.
 * @details Работает с копиями заказа и склада; статус реального заказа и содержимое склада обновляет вызывающий код.
 */
class Shipment
{
private:
    Order order_; /**< Отгружаемый заказ (копия). */
    Warehouse warehouse_; /**< Склад (копия). */

public:
    /**
     * @brief Создаёт отгрузку.
     * @param order Заказ.
     * @param warehouse Склад.
     */
    Shipment(Order order, Warehouse warehouse);
    /**
     * @brief Отгружает заказ: переводит его в статус «Shipped».
     */
    void ship();
};
