#include <gtest/gtest.h>
#include "lab2/common/Discount.hpp"

// 10% от 200 -> 180
TEST(Discount, AppliesPercent)
{
    Discount d("Акция", 10);
    EXPECT_DOUBLE_EQ(d.apply(200.0), 180.0);
}

// Нулевая скидка цену не меняет
TEST(Discount, ZeroPercentKeepsPrice)
{
    Discount d("Без скидки", 0);
    EXPECT_DOUBLE_EQ(d.apply(55.5), 55.5);
}

// 100% -> бесплатно
TEST(Discount, FullDiscount)
{
    Discount d("Подарок", 100);
    EXPECT_DOUBLE_EQ(d.apply(99.0), 0.0);
}

// Нулевая цена остаётся нулевой
TEST(Discount, ZeroPrice)
{
    Discount d("Акция", 50);
    EXPECT_DOUBLE_EQ(d.apply(0.0), 0.0);
}
