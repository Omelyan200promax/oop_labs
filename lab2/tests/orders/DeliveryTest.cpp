#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Delivery.hpp"
#include "lab2/exceptions/DeliveryFailedException.hpp"

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

// Новая доставка не завершена
TEST(Delivery, NotDeliveredInitially)
{
    Delivery d(makeOrder(), Address("Минск", "ул. Ленина, 5"));
    EXPECT_FALSE(d.isDelivered());
}

// Начатая доставка завершается успешно
TEST(Delivery, StartThenCompleteDelivers)
{
    Delivery d(makeOrder(), Address("Минск", "ул. Ленина, 5"));
    d.startDelivery();
    d.completeDelivery();
    EXPECT_TRUE(d.isDelivered());
}

// Завершить, не начав, нельзя
TEST(Delivery, CompleteWithoutStartThrows)
{
    Delivery d(makeOrder(), Address("Минск", "ул. Ленина, 5"));
    EXPECT_THROW(d.completeDelivery(), DeliveryFailedException);
    EXPECT_FALSE(d.isDelivered());
}

// Повторное завершение уже доставленного заказа — ошибка
TEST(Delivery, CompleteTwiceThrows)
{
    Delivery d(makeOrder(), Address("Минск", "ул. Ленина, 5"));
    d.startDelivery();
    d.completeDelivery();
    EXPECT_THROW(d.completeDelivery(), DeliveryFailedException);
    EXPECT_TRUE(d.isDelivered());
}
