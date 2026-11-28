#include <gtest/gtest.h>
#include "lab2/common/ContactInfo.hpp"

// Email возвращается как был передан
TEST(ContactInfo, ReturnsEmail)
{
    ContactInfo c("+375291112233", "user@bsuir.by");
    EXPECT_EQ(c.getEmail(), "user@bsuir.by");
}

// Пустой email допустим (валидации нет)
TEST(ContactInfo, EmptyEmailAllowed)
{
    ContactInfo c("+375291112233", "");
    EXPECT_EQ(c.getEmail(), "");
}

// Копия хранит те же данные
TEST(ContactInfo, CopyKeepsEmail)
{
    ContactInfo a("1", "a@b.c");
    ContactInfo b = a;
    EXPECT_EQ(b.getEmail(), "a@b.c");
}
