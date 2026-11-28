#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Accountant.hpp"

static Accountant makeAccountant()
{
    return Accountant("Ольга", 5, 2000.0, Role("Бухгалтер", 4), "123456789");
}

// Унаследованные геттеры работают
TEST(Accountant, InheritedGetters)
{
    Accountant a = makeAccountant();
    EXPECT_EQ(a.getName(), "Ольга");
    EXPECT_DOUBLE_EQ(a.getSalary(), 2000.0);
    EXPECT_EQ(a.getRole().getAccessLevel(), 4);
}

// work() печатает сообщение о начислении зарплаты
TEST(Accountant, WorkPrintsMessage)
{
    Accountant a = makeAccountant();
    testing::internal::CaptureStdout();
    a.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Ольга") != std::string::npos);
    EXPECT_TRUE(out.find("начисляет зарплату") != std::string::npos);
}

// calculateSalary выводит сумму и имя сотрудника
TEST(Accountant, CalculateSalaryPrintsEmployeeData)
{
    Accountant a = makeAccountant();
    Employee emp("Иван", 1, 1800, Role("Кладовщик", 3));
    testing::internal::CaptureStdout();
    a.calculateSalary(emp);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("1800") != std::string::npos);
    EXPECT_TRUE(out.find("Иван") != std::string::npos);
    EXPECT_TRUE(out.find("BYN") != std::string::npos);
}

// Бухгалтер может начислить зарплату самому себе (ссылка на Employee)
TEST(Accountant, CalculateSalaryForItself)
{
    Accountant a = makeAccountant();
    testing::internal::CaptureStdout();
    a.calculateSalary(a);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("2000") != std::string::npos);
}
