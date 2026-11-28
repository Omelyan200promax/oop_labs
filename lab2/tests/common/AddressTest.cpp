#include <gtest/gtest.h>
#include "lab2/common/Address.hpp"

// Полный адрес: "город, улица"
TEST(Address, FullAddressFormat)
{
    Address a("Минск", "ул. Козлова, 15");
    EXPECT_EQ(a.getFullAddress(), "Минск, ул. Козлова, 15");
}

// Пустые поля не приводят к ошибке
TEST(Address, EmptyFields)
{
    Address a("", "");
    EXPECT_EQ(a.getFullAddress(), ", ");
}

// Копия адреса равна оригиналу
TEST(Address, CopyKeepsValue)
{
    Address a("Брест", "ул. Ленина");
    Address b = a;
    EXPECT_EQ(b.getFullAddress(), a.getFullAddress());
}
