#include <gtest/gtest.h>
#include "lab2/people/SystemUser.hpp"

// Пользователь с высокой ролью проходит проверку уровня
TEST(SystemUser, LoginAsAllowedForHighRole)
{
    SystemUser u("boss", Role("Менеджер", 5));
    EXPECT_TRUE(u.loginAs(5));
    EXPECT_TRUE(u.loginAs(2));
}

// Пользователь с низкой ролью не проходит проверку
TEST(SystemUser, LoginAsDeniedForLowRole)
{
    SystemUser u("courier1", Role("Курьер", 2));
    EXPECT_FALSE(u.loginAs(4));
}

// Граница: равный уровень допускается
TEST(SystemUser, LoginAsBoundaryLevel)
{
    SystemUser u("acc", Role("Бухгалтер", 4));
    EXPECT_TRUE(u.loginAs(4));
    EXPECT_FALSE(u.loginAs(5));
}

// Проверка на константном объекте (loginAs — const-метод)
TEST(SystemUser, LoginAsWorksOnConstObject)
{
    const SystemUser u("keeper", Role("Кладовщик", 3));
    EXPECT_TRUE(u.loginAs(3));
}
