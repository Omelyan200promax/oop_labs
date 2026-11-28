#include <gtest/gtest.h>
#include "lab2/common/Review.hpp"

// Текст и автор сохраняются
TEST(Review, StoresTextAndAuthor)
{
    Review r("Отличная книга", "Анна");
    EXPECT_EQ(r.getText(), "Отличная книга");
    EXPECT_EQ(r.getAuthor(), "Анна");
}

// Пустые поля допустимы
TEST(Review, EmptyFields)
{
    Review r("", "");
    EXPECT_EQ(r.getText(), "");
    EXPECT_EQ(r.getAuthor(), "");
}
