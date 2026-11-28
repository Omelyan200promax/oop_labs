#include <gtest/gtest.h>
#include "lab2/warehouse/WarehouseZone.hpp"

// Геттеры возвращают переданные значения
TEST(WarehouseZone, Getters)
{
    WarehouseZone z("Сухая зона", 80);
    EXPECT_EQ(z.getName(), "Сухая зона");
    EXPECT_EQ(z.getCapacity(), 80);
}

// Копия зоны сохраняет данные
TEST(WarehouseZone, CopyKeepsData)
{
    WarehouseZone z("Зона B", 60);
    WarehouseZone copy = z;
    EXPECT_EQ(copy.getName(), "Зона B");
    EXPECT_EQ(copy.getCapacity(), 60);
}
