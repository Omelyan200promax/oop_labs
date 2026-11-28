#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/ReturnRequest.hpp"

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

// Новый запрос не одобрен
TEST(ReturnRequest, NotApprovedInitially)
{
    ReturnRequest r(makeOrder(), "брак");
    EXPECT_FALSE(r.isApproved());
}

// После approve() одобрен
TEST(ReturnRequest, ApproveMarksApproved)
{
    ReturnRequest r(makeOrder(), "брак");
    r.approve();
    EXPECT_TRUE(r.isApproved());
}

// Повторное одобрение безопасно
TEST(ReturnRequest, ApproveTwiceStaysApproved)
{
    ReturnRequest r(makeOrder(), "не подошла");
    r.approve();
    r.approve();
    EXPECT_TRUE(r.isApproved());
}

// Копия запроса сохраняет состояние
TEST(ReturnRequest, CopyKeepsApprovalState)
{
    ReturnRequest r(makeOrder(), "брак");
    r.approve();
    ReturnRequest copy = r;
    EXPECT_TRUE(copy.isApproved());
}
