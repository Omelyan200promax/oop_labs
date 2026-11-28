#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Manager.hpp"

static Manager makeManager()
{
    return Manager("Алексей", 1, 2500.0, Role("Менеджер", 5), "Отдел продаж");
}

// Унаследованные геттеры
TEST(Manager, InheritedGetters)
{
    Manager m = makeManager();
    EXPECT_EQ(m.getName(), "Алексей");
    EXPECT_DOUBLE_EQ(m.getSalary(), 2500.0);
    EXPECT_TRUE(m.getRole().hasAccess(5));
}

// work() упоминает название отдела
TEST(Manager, WorkMentionsDepartment)
{
    Manager m = makeManager();
    testing::internal::CaptureStdout();
    m.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("управляет отделом \"Отдел продаж\"") != std::string::npos);
}

// createReport() сообщает о формировании отчёта
TEST(Manager, CreateReportPrintsMessage)
{
    Manager m = makeManager();
    testing::internal::CaptureStdout();
    m.createReport();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("формирует отчет по продажам") != std::string::npos);
}

// applyDiscountToBook() сообщает о применении скидки
TEST(Manager, ApplyDiscountPrintsMessage)
{
    Manager m = makeManager();
    testing::internal::CaptureStdout();
    m.applyDiscountToBook();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("применяет скидку к книге") != std::string::npos);
}
