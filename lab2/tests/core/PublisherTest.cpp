#include <gtest/gtest.h>
#include "lab2/core/Publisher.hpp"

// Информация: "Название (город)"
TEST(Publisher, InfoFormat)
{
    Publisher p("Азбука", "СПб");
    EXPECT_EQ(p.getInfo(), "Азбука (СПб)");
}

// Пустые поля
TEST(Publisher, EmptyFields)
{
    Publisher p("", "");
    EXPECT_EQ(p.getInfo(), " ()");
}
