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
    double total = 0;
    for (const auto &b : books_)
    {
        total += b.getPriceAmount();
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
Customer Order::getCustomer() const { return customer_; }