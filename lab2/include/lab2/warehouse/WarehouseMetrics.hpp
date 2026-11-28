/**
 * @file WarehouseMetrics.hpp
 * @brief Класс WarehouseMetrics — метрики склада.
 */
#pragma once

/**
 * @brief Накопительные метрики по заказам.
 */
class WarehouseMetrics
{
private:
    int totalBooks_; /**< Всего книг в заказах. */
    int totalOrders_; /**< Всего заказов. */

public:
    /**
     * @brief Создаёт метрики с нулевыми счётчиками.
     */
    WarehouseMetrics();
    /**
     * @brief Учитывает книги.
     * @param count Сколько книг добавить к счётчику.
     */
    void addBooks(int count);
    /**
     * @brief Учитывает один заказ.
     */
    void addOrder();
    /**
     * @brief Среднее число книг в заказе.
     * @return Целая часть отношения книг к заказам; 0, если заказов нет.
     */
    int getAverageBooksPerOrder() const;
};
