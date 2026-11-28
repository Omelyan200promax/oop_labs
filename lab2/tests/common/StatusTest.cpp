#include <gtest/gtest.h>
#include "lab2/common/Status.hpp"

// Название статуса сохраняется
TEST(Status, StoresName)
{
    Status s("Paid");
    EXPECT_EQ(s.getName(), "Paid");
}

// Копия хранит то же название
TEST(Status, CopyKeepsName)
{
    Status a("Shipped");
    Status b = a;
    EXPECT_EQ(b.getName(), "Shipped");
}
