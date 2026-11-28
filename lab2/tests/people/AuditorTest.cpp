#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Auditor.hpp"

static Auditor makeAuditor()
{
    return Auditor("Вероника", 4, 2200.0, Role("Аудитор", 4));
}

// Унаследованные геттеры
TEST(Auditor, InheritedGetters)
{
    Auditor a = makeAuditor();
    EXPECT_EQ(a.getName(), "Вероника");
    EXPECT_DOUBLE_EQ(a.getSalary(), 2200.0);
    EXPECT_EQ(a.getRole().getTitle(), "Аудитор");
}

// work() печатает сообщение об аудите
TEST(Auditor, WorkPrintsMessage)
{
    Auditor a = makeAuditor();
    testing::internal::CaptureStdout();
    a.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Вероника") != std::string::npos);
    EXPECT_TRUE(out.find("проводит аудит склада") != std::string::npos);
}

// checkInventory() сообщает о запуске проверки
TEST(Auditor, CheckInventoryPrintsMessage)
{
    Auditor a = makeAuditor();
    testing::internal::CaptureStdout();
    a.checkInventory();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("запускает проверку инвентаризации") != std::string::npos);
}

// Вызов через указатель на базовый класс использует переопределённый work()
TEST(Auditor, WorkIsVirtual)
{
    Auditor a = makeAuditor();
    Employee *e = &a;
    testing::internal::CaptureStdout();
    e->work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("аудит") != std::string::npos);
}
