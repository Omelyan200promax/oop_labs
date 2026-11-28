#include <gtest/gtest.h>
#include "lab2/core/Author.hpp"

// Полное имя: "Имя Фамилия"
TEST(Author, FullName)
{
    Author a("Лев", "Толстой", "Россия", 1828, 1910);
    EXPECT_EQ(a.getFullName(), "Лев Толстой");
}

// Годы жизни
TEST(Author, Years)
{
    Author a("Лев", "Толстой", "Россия", 1828, 1910);
    EXPECT_EQ(a.getBirthYear(), 1828);
    EXPECT_EQ(a.getDeathYear(), 1910);
}

// Значения по умолчанию: 1800 и 0 (жив)
TEST(Author, DefaultYears)
{
    Author a("Иван", "Иванов", "Беларусь");
    EXPECT_EQ(a.getBirthYear(), 1800);
    EXPECT_EQ(a.getDeathYear(), 0);
}
