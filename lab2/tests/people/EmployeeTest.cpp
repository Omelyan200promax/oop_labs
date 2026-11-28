#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include "lab2/people/Employee.hpp"
#include "lab2/people/Manager.hpp"
#include "lab2/people/Courier.hpp"
#include "lab2/people/Storekeeper.hpp"

// Геттеры базового класса
TEST(Employee, Getters)
{
    Employee e("Иван Иванов", 1, 1500.5, Role("Рабочий", 1));
    EXPECT_EQ(e.getName(), "Иван Иванов");
    EXPECT_DOUBLE_EQ(e.getSalary(), 1500.5);
    EXPECT_EQ(e.getRole().getTitle(), "Рабочий");
    EXPECT_EQ(e.getRole().getAccessLevel(), 1);
}

// Базовая реализация work() печатает имя и «базовую работу»
TEST(Employee, BaseWorkPrintsMessage)
{
    Employee e("Пётр", 2, 1000, Role("Рабочий", 1));
    testing::internal::CaptureStdout();
    e.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Пётр") != std::string::npos);
    EXPECT_TRUE(out.find("базовую работу") != std::string::npos);
}

// Полиморфизм: через указатель на базовый класс вызывается work() наследника
TEST(Employee, PolymorphicWorkCallsOverride)
{
    std::vector<std::shared_ptr<Employee>> staff;
    staff.push_back(std::make_shared<Manager>("Алексей", 1, 2500, Role("Менеджер", 5), "Продажи"));
    staff.push_back(std::make_shared<Courier>("Платон", 2, 1500, Role("Курьер", 2), "Фургон"));
    staff.push_back(std::make_shared<Storekeeper>("Никита", 3, 1800, Role("Кладовщик", 3), "Ночная"));

    testing::internal::CaptureStdout();
    for (auto &e : staff)
        e->work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("управляет отделом \"Продажи\"") != std::string::npos);
    EXPECT_TRUE(out.find("доставляет заказы на \"Фургон\"") != std::string::npos);
    EXPECT_TRUE(out.find("принимает товар в смену \"Ночная\"") != std::string::npos);
    EXPECT_TRUE(out.find("базовую работу") == std::string::npos); // базовая версия не вызывалась
}

// dynamic_cast позволяет определить конкретный тип сотрудника
TEST(Employee, DynamicCastIdentifiesDerivedType)
{
    std::shared_ptr<Employee> e = std::make_shared<Manager>("А", 1, 1, Role("Менеджер", 5), "О");
    EXPECT_TRUE(dynamic_cast<Manager *>(e.get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<Courier *>(e.get()) == nullptr);
}

// Роль возвращается копией, изменение копии не влияет на сотрудника
TEST(Employee, GetRoleReturnsCopy)
{
    Employee e("Е", 1, 1, Role("Рабочий", 1));
    Role r = e.getRole();
    r = Role("Другая", 9);
    EXPECT_EQ(e.getRole().getTitle(), "Рабочий");
}
