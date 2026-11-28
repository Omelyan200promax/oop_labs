#include <gtest/gtest.h>
#include "lab2/common/Rating.hpp"

// Без оценок рейтинг 0
TEST(Rating, EmptyIsZero)
{
    Rating r;
    EXPECT_DOUBLE_EQ(r.getScore(), 0.0);
}

// Среднее арифметическое оценок
TEST(Rating, Average)
{
    Rating r;
    r.addScore(5);
    r.addScore(4);
    r.addScore(3);
    EXPECT_DOUBLE_EQ(r.getScore(), 4.0);
}

// Оценки вне диапазона 1..5 игнорируются
TEST(Rating, OutOfRangeIgnored)
{
    Rating r;
    r.addScore(0);
    r.addScore(6);
    r.addScore(-3);
    EXPECT_DOUBLE_EQ(r.getScore(), 0.0);
    r.addScore(2);
    EXPECT_DOUBLE_EQ(r.getScore(), 2.0);
}

// Граничные значения 1 и 5 допустимы
TEST(Rating, BoundariesAccepted)
{
    Rating r;
    r.addScore(1);
    r.addScore(5);
    EXPECT_DOUBLE_EQ(r.getScore(), 3.0);
}
