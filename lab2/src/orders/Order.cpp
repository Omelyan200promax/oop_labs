#include "lab2/orders/Order.hpp"
#include "lab2/exceptions/InvalidOrderException.hpp"

Order::Order(int id, Customer customer, CustomDate date)
    : id_(id), customer_(customer), orderDate_(date), status_("Created") {}

void Order::addBook(Book book)
{
    books_.push_back(book);
}

double Order::calculateTotal() const
{
    // Упрощенно считаем сумму без учета скидок и валюты (т.к. Price хранит строку)
    double total = 0;
    for (const auto &b : books_)
    {
        // В учебных целях просто возвращаем количество книг * 500
        total += 500.0;
    }
    return total;
}

void Order::changeStatus(std::string newStatus)
{
    if (books_.empty() && newStatus == "Paid")
    {
        throw InvalidOrderException("Нельзя оплатить пустой заказ");
    }
    status_ = newStatus;
}

std::string Order::getStatus() const { return status_; }
