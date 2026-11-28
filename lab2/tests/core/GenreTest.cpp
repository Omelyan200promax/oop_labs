#include <gtest/gtest.h>
#include "lab2/core/Genre.hpp"

// Название жанра
TEST(Genre, Name)
{
    Genre g("Роман", "Крупная проза");
    EXPECT_EQ(g.getName(), "Роман");
}

// Описание: "Название: описание"
TEST(Genre, DescriptionFormat)
{
    Genre g("Роман", "Крупная проза");
    EXPECT_EQ(g.getDescription(), "Роман: Крупная проза");
}

// Пустое описание
TEST(Genre, EmptyDescription)
{
    Genre g("Пьеса", "");
    EXPECT_EQ(g.getDescription(), "Пьеса: ");
}
