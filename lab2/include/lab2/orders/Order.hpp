/**
 * @file Order.hpp
 * @brief Класс Order — заказ клиента.
 */
#pragma once
#include <vector>
#include <string>
#include "lab2/people/Customer.hpp"
#include "lab2/core/Book.hpp"
#include "lab2/common/CustomDate.hpp"

/**
 * @brief Заказ клиента на одну или несколько книг.
 * @details Статус хранится строкой: Created (создан), Paid (оплачен), Shipped (отгружен), In Delivery (в доставке), Delivered (доставлен), Cancelled (отменён), Returned (возвращён). Новый заказ получает статус Created.
 */
class Order
{
private:
    int id_; /**< Номер заказа. */
    Customer customer_; /**< Клиент (копия). */
    std::vector<Book> books_; /**< Книги в заказе. */
    CustomDate orderDate_; /**< Дата оформления. */
    std::string status_; /**< Текущий статус. */

public:
    /**
     * @brief Создаёт заказ со статусом Created и без книг.
     * @param id Номер заказа.
     * @param customer Клиент.
     * @param date Дата оформления.
     */
    Order(int id, Customer customer, CustomDate date);
    /**
     * @brief Добавляет книгу в заказ.
     * @param book Книга.
     */
    void addBook(Book book);
    /**
     * @brief Считает стоимость заказа.
     * @return Сумма цен всех книг.
     */
    double calculateTotal() const;
    /**
     * @brief Меняет статус заказа.
     * @param newStatus Новый статус.
     * @throws InvalidOrderException Если пытаются перевести пустой заказ в статус Paid.
     */
    void changeStatus(std::string newStatus);

    /**
     * @brief Текущий статус.
     * @return Строка статуса.
     */
    std::string getStatus() const;
    /**
     * @brief Клиент заказа.
     * @return Копия клиента.
     */
    Customer getCustomer() const;
    /**
     * @brief Название первой книги.
     * @return Название или «Пусто», если книг нет.
     */
    std::string getFirstBookTitle() const;
    /**
     * @brief Номер заказа.
     * @return Идентификатор.
     */
    int getId() const;
    /**
     * @brief Названия книг заказа.
     * @return Названия по одному на экземпляр.
     */
    std::vector<std::string> getBookTitles() const;
    /**
     * @brief Дата оформления.
     * @return Дата.
     */
    CustomDate getDate() const;
};
