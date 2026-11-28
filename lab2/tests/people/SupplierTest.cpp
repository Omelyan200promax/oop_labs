#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Supplier.hpp"

// Вспомогательная функция: книга с заданным остатком
static Book makeBook(int stock)
{
    return Book("Мастер и Маргарита", "978-5", Author("Михаил", "Булгаков", "Россия", 1891, 1940),
                Publisher("Азбука", "СПб"), Genre("Роман", "Проза"), Category("Классика", "Классика"),
                Language("Русский", "ru"), CoverType("Твердая", true), Price(30.0, "BYN"),
                Dimensions(20, 13, 4), CustomDate(1, 1, 2020), stock);
}

static Supplier makeSupplier()
{
    return Supplier("ООО Книжный мир", ContactInfo("+375172001122", "info@kmir.by"));
}

// Поставка увеличивает остаток книги и печатает сообщение
TEST(Supplier, SupplyBooksIncreasesStock)
{
    Supplier s = makeSupplier();
    Book b = makeBook(2);
    testing::internal::CaptureStdout();
    s.supplyBooks(b, 5);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(b.getStockCount(), 7);
    EXPECT_TRUE(out.find("ООО Книжный мир") != std::string::npos);
    EXPECT_TRUE(out.find("5 шт.") != std::string::npos);
    EXPECT_TRUE(out.find("Мастер и Маргарита") != std::string::npos);
}

// Нулевая поставка ничего не меняет и ничего не печатает
TEST(Supplier, ZeroCountDoesNothing)
{
    Supplier s = makeSupplier();
    Book b = makeBook(3);
    testing::internal::CaptureStdout();
    s.supplyBooks(b, 0);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(b.getStockCount(), 3);
    EXPECT_TRUE(out.empty());
}

// Отрицательное количество игнорируется
TEST(Supplier, NegativeCountIgnored)
{
    Supplier s = makeSupplier();
    Book b = makeBook(3);
    testing::internal::CaptureStdout();
    s.supplyBooks(b, -4);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(b.getStockCount(), 3);
}

// Несколько поставок суммируются
TEST(Supplier, SeveralSuppliesAccumulate)
{
    Supplier s = makeSupplier();
    Book b = makeBook(0);
    testing::internal::CaptureStdout();
    s.supplyBooks(b, 2);
    s.supplyBooks(b, 3);
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(b.getStockCount(), 5);
}
