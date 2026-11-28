#include <gtest/gtest.h>
#include "lab2/people/Role.hpp"

// Геттеры возвращают переданные данные
TEST(Role, Getters)
{
    Role r("Менеджер", 5);
    EXPECT_EQ(r.getTitle(), "Менеджер");
    EXPECT_EQ(r.getAccessLevel(), 5);
}

// Доступ есть, если уровень роли не ниже требуемого
TEST(Role, HasAccessWhenLevelIsEnough)
{
    Role r("Аудитор", 4);
    EXPECT_TRUE(r.hasAccess(1));
    EXPECT_TRUE(r.hasAccess(4)); // граница включается
}

// Доступа нет, если требуемый уровень выше
TEST(Role, NoAccessWhenLevelIsTooLow)
{
    Role r("Курьер", 2);
    EXPECT_FALSE(r.hasAccess(3));
    EXPECT_FALSE(r.hasAccess(5));
}

// Нулевой уровень даёт доступ только к уровню 0
TEST(Role, ZeroLevelRole)
{
    Role r("Гость", 0);
    EXPECT_TRUE(r.hasAccess(0));
    EXPECT_FALSE(r.hasAccess(1));
}
