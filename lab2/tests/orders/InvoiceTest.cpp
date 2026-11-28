#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Invoice.hpp"

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

// До generate() сумма счёта 0
TEST(Invoice, AmountIsZeroBeforeGenerate)
{
    Invoice inv(1, makeOrder());
    EXPECT_DOUBLE_EQ(inv.getAmount(), 0.0);
}

// После generate() сумма равна сумме заказа
TEST(Invoice, GenerateUsesOrderTotal)
{
    Invoice inv(1, makeOrder());
    inv.generate();
    EXPECT_DOUBLE_EQ(inv.getAmount(), 150.0);
}

// Счёт по пустому заказу — 0
TEST(Invoice, EmptyOrderGivesZero)
{
    Invoice inv(2, Order(1, makeCustomer(), CustomDate(1, 1, 2026)));
    inv.generate();
    EXPECT_DOUBLE_EQ(inv.getAmount(), 0.0);
}

// Счёт хранит копию заказа: позднее изменение оригинала не влияет
TEST(Invoice, KeepsCopyOfOrder)
{
    Order o = makeOrder();
    Invoice inv(1, o);
    o.addBook(makeBook("C", 1000.0));
    inv.generate();
    EXPECT_DOUBLE_EQ(inv.getAmount(), 150.0);
}
