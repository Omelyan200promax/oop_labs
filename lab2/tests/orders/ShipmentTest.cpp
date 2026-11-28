#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Shipment.hpp"
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


static Warehouse makeWarehouse()
{
    return Warehouse("Главный склад", Address("Минск", "ул. Складская, 1"), ContactInfo("+375170000000", "sklad@bsuir.by"));
}

// Создание отгрузки и вызов ship() не бросает исключений
TEST(Shipment, ShipDoesNotThrowForValidOrder)
{
    Shipment s(makeOrder(), makeWarehouse());
    EXPECT_NO_THROW(s.ship());
}

// Shipment работает с копией: исходный заказ не меняется
TEST(Shipment, DoesNotModifyOriginalOrder)
{
    Order o = makeOrder();
    o.changeStatus("Paid");
    Shipment s(o, makeWarehouse());
    s.ship();
    EXPECT_EQ(o.getStatus(), "Paid");
}

// Отгрузка пустого заказа тоже допустима (статус не «Paid»)
TEST(Shipment, ShipEmptyOrderDoesNotThrow)
{
    Shipment s(Order(1, makeCustomer(), CustomDate(1, 1, 2026)), makeWarehouse());
    EXPECT_NO_THROW(s.ship());
}
