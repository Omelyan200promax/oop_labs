#include <gtest/gtest.h>
#include "lab2/warehouse/Equipment.hpp"

// Название и состояние сохраняются
TEST(Equipment, GettersReturnGivenValues)
{
    Equipment e("Погрузчик", true);
    EXPECT_EQ(e.getName(), "Погрузчик");
    EXPECT_TRUE(e.checkStatus());
}

// Сломанное оборудование
TEST(Equipment, BrokenEquipmentReportsFalse)
{
    Equipment e("Сканер", false);
    EXPECT_FALSE(e.checkStatus());
}

// После ремонта оборудование работает
TEST(Equipment, RepairFixesEquipment)
{
    Equipment e("Сканер", false);
    e.repair();
    EXPECT_TRUE(e.checkStatus());
}

// Ремонт исправного оборудования ничего не ломает
TEST(Equipment, RepairWorkingEquipmentKeepsWorking)
{
    Equipment e("Фургон", true);
    e.repair();
    EXPECT_TRUE(e.checkStatus());
    EXPECT_EQ(e.getName(), "Фургон");
}
