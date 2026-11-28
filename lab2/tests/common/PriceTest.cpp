#include <gtest/gtest.h>
#include <stdexcept>
#include "lab2/common/Price.hpp"

// Сумма и строковое представление
TEST(Price, AmountAndToString)
{
    Price p(25.5, "BYN");
    EXPECT_DOUBLE_EQ(p.getAmount(), 25.5);
    EXPECT_EQ(p.toString(), "25.5 BYN");
}

// Отрицательная цена недопустима
TEST(Price, NegativeThrows)
{
    EXPECT_THROW(Price(-1.0, "BYN"), std::invalid_argument);
}

// Нулевая цена допустима
TEST(Price, ZeroAllowed)
{
    EXPECT_NO_THROW(Price(0.0, "BYN"));
}

// Скидка в допустимом диапазоне применяется
TEST(Price, ApplyDiscount)
{
    Price p(200.0, "BYN");
    p.applyDiscount(25);
    EXPECT_DOUBLE_EQ(p.getAmount(), 150.0);
}

// Скидка 100% обнуляет цену
TEST(Price, FullDiscount)
{
    Price p(80.0, "BYN");
    p.applyDiscount(100);
    EXPECT_DOUBLE_EQ(p.getAmount(), 0.0);
}

// Скидка вне диапазона (0; 100] игнорируется
TEST(Price, InvalidDiscountIgnored)
{
    Price p(100.0, "BYN");
    p.applyDiscount(0);
    p.applyDiscount(-10);
    p.applyDiscount(150);
    EXPECT_DOUBLE_EQ(p.getAmount(), 100.0);
}
