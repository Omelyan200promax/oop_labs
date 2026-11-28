#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Refund.hpp"
#include "lab2/exceptions/InvalidOrderException.hpp"

// Вспомогательные функции: клиент, книга и заказ
static Customer makeCustomer(double balance = 500.0)
{
    return Customer("Анна", ContactInfo("+375291112233", "anna@bsuir.by"), Address("Минск", "ул. Козлова, 15"), balance);
}

static Book makeBook(const std::string &title = "Книга", double price = 100.0)
{
    return Book(title, "978-" + title, Author("Лев", "Толстой", "Россия", 1828, 1910),
                Publisher("Азбука", "СПб"), Genre("Роман", "Проза"), Category("Классика", "Классика"),
                Language("Русский", "ru"), CoverType("Твердая", true), Price(price, "BYN"),
                Dimensions(10, 10, 10), CustomDate(1, 1, 2020), 5);
}

static Order makeOrder()
{
    Order o(1, makeCustomer(), CustomDate(28, 11, 2026));
    o.addBook(makeBook("A", 100.0));
    o.addBook(makeBook("B", 50.0));
    return o;
}

// Сумма возврата
TEST(Refund, GetAmount)
{
    Refund r(ReturnRequest(makeOrder(), "брак"), Price(150.0, "BYN"));
    EXPECT_DOUBLE_EQ(r.getAmount(), 150.0);
}

// Без одобрения возврат невозможен
TEST(Refund, ProcessWithoutApprovalThrows)
{
    Refund r(ReturnRequest(makeOrder(), "брак"), Price(150.0, "BYN"));
    EXPECT_THROW(r.processRefund(), InvalidOrderException);
}

// Одобренный возврат проходит
TEST(Refund, ProcessApprovedSucceeds)
{
    ReturnRequest req(makeOrder(), "брак");
    req.approve();
    Refund r(req, Price(150.0, "BYN"));
    EXPECT_NO_THROW(r.processRefund());
}

// Одобрение оригинала после создания Refund не влияет на копию внутри
TEST(Refund, KeepsCopyOfRequest)
{
    ReturnRequest req(makeOrder(), "брак");
    Refund r(req, Price(10.0, "BYN"));
    req.approve();
    EXPECT_THROW(r.processRefund(), InvalidOrderException);
}
