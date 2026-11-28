#include <gtest/gtest.h>
#include "lab2/warehouse/WarehouseMetrics.hpp"

// Без заказов среднее равно 0 (нет деления на ноль)
TEST(WarehouseMetrics, AverageIsZeroWithoutOrders)
{
    WarehouseMetrics m;
    EXPECT_EQ(m.getAverageBooksPerOrder(), 0);
}

// Даже если книги учтены, без заказов среднее 0
TEST(WarehouseMetrics, AverageIsZeroWithBooksButNoOrders)
{
    WarehouseMetrics m;
    m.addBooks(5);
    EXPECT_EQ(m.getAverageBooksPerOrder(), 0);
}

// Среднее число книг на заказ
TEST(WarehouseMetrics, AverageBooksPerOrder)
{
    WarehouseMetrics m;
    m.addOrder();
    m.addBooks(2);
    m.addOrder();
    m.addBooks(4);
    EXPECT_EQ(m.getAverageBooksPerOrder(), 3);
}

// Среднее целое: дробная часть отбрасывается
TEST(WarehouseMetrics, AverageIsIntegerDivision)
{
    WarehouseMetrics m;
    m.addOrder();
    m.addOrder();
    m.addBooks(5);
    EXPECT_EQ(m.getAverageBooksPerOrder(), 2);
}
