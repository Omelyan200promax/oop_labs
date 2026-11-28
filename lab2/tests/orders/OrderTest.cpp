#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
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

// Новый заказ в статусе Created
TEST(Order, NewOrderIsCreated)
{
    Order o(7, makeCustomer(), CustomDate(28, 11, 2026));
    EXPECT_EQ(o.getId(), 7);
    EXPECT_EQ(o.getStatus(), "Created");
    EXPECT_EQ(o.getDate().toString(), "28.11.2026");
    EXPECT_EQ(o.getCustomer().getName(), "Анна");
}

// Сумма — это сумма цен книг
TEST(Order, CalculateTotal)
{
    EXPECT_DOUBLE_EQ(makeOrder().calculateTotal(), 150.0);
}

// У пустого заказа сумма 0 и «Пусто» вместо первой книги
TEST(Order, EmptyOrderTotalAndFirstTitle)
{
    Order o(1, makeCustomer(), CustomDate(1, 1, 2026));
    EXPECT_DOUBLE_EQ(o.calculateTotal(), 0.0);
    EXPECT_EQ(o.getFirstBookTitle(), "Пусто");
    EXPECT_TRUE(o.getBookTitles().empty());
}

// Названия книг в порядке добавления
TEST(Order, BookTitlesKeepOrder)
{
    Order o = makeOrder();
    auto titles = o.getBookTitles();
    ASSERT_EQ(titles.size(), 2u);
    EXPECT_EQ(titles[0], "A");
    EXPECT_EQ(titles[1], "B");
    EXPECT_EQ(o.getFirstBookTitle(), "A");
}

// Смена статуса
TEST(Order, ChangeStatus)
{
    Order o = makeOrder();
    o.changeStatus("Paid");
    EXPECT_EQ(o.getStatus(), "Paid");
    o.changeStatus("Shipped");
    EXPECT_EQ(o.getStatus(), "Shipped");
}

// Пустой заказ нельзя оплатить
TEST(Order, PayingEmptyOrderThrows)
{
    Order o(1, makeCustomer(), CustomDate(1, 1, 2026));
    EXPECT_THROW(o.changeStatus("Paid"), InvalidOrderException);
    EXPECT_EQ(o.getStatus(), "Created");
}

// Другие статусы у пустого заказа допустимы (например, отмена)
TEST(Order, EmptyOrderCanBeCancelled)
{
    Order o(1, makeCustomer(), CustomDate(1, 1, 2026));
    EXPECT_NO_THROW(o.changeStatus("Cancelled"));
    EXPECT_EQ(o.getStatus(), "Cancelled");
}
