#include <gtest/gtest.h>
#include "lab2/core/Category.hpp"

// Название категории
TEST(Category, Name)
{
    Category c("Классика", "Классическая литература");
    EXPECT_EQ(c.getName(), "Классика");
}

// Пустое название допустимо
TEST(Category, EmptyName)
{
    Category c("", "");
    EXPECT_EQ(c.getName(), "");
}
