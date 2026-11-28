#include <gtest/gtest.h>
#include "lab2/common/CustomDate.hpp"

// Геттеры возвращают переданные значения
TEST(CustomDate, Getters)
{
    CustomDate d(5, 11, 2026);
    EXPECT_EQ(d.getDay(), 5);
    EXPECT_EQ(d.getMonth(), 11);
    EXPECT_EQ(d.getYear(), 2026);
}

// Строка формата ДД.ММ.ГГГГ с ведущими нулями
TEST(CustomDate, ToStringPadsWithZeros)
{
    EXPECT_EQ(CustomDate(5, 3, 2026).toString(), "05.03.2026");
    EXPECT_EQ(CustomDate(25, 12, 1999).toString(), "25.12.1999");
}

// Високосные годы: делится на 4, кроме столетий, кроме кратных 400
TEST(CustomDate, LeapYear)
{
    EXPECT_TRUE(CustomDate(1, 1, 2024).isLeapYear());
    EXPECT_TRUE(CustomDate(1, 1, 2000).isLeapYear());
    EXPECT_FALSE(CustomDate(1, 1, 1900).isLeapYear());
    EXPECT_FALSE(CustomDate(1, 1, 2023).isLeapYear());
}

// Сравнение: по году, затем по месяцу, затем по дню
TEST(CustomDate, LessOrEqualByYearMonthDay)
{
    EXPECT_TRUE(CustomDate(1, 1, 2025) <= CustomDate(1, 1, 2026));
    EXPECT_FALSE(CustomDate(1, 1, 2027) <= CustomDate(31, 12, 2026));
    EXPECT_TRUE(CustomDate(31, 1, 2026) <= CustomDate(1, 2, 2026));
    EXPECT_FALSE(CustomDate(1, 3, 2026) <= CustomDate(28, 2, 2026));
    EXPECT_TRUE(CustomDate(10, 5, 2026) <= CustomDate(11, 5, 2026));
}

// Равные даты: <= истинно в обе стороны
TEST(CustomDate, EqualDatesAreLessOrEqual)
{
    CustomDate a(10, 5, 2026), b(10, 5, 2026);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b <= a);
}
