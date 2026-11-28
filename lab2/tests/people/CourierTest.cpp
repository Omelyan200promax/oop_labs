#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Courier.hpp"

static Courier makeCourier()
{
    return Courier("Платон", 3, 1500.0, Role("Курьер", 2), "Фургон");
}

// Унаследованные геттеры
TEST(Courier, InheritedGetters)
{
    Courier c = makeCourier();
    EXPECT_EQ(c.getName(), "Платон");
    EXPECT_DOUBLE_EQ(c.getSalary(), 1500.0);
    EXPECT_EQ(c.getRole().getAccessLevel(), 2);
}

// work() упоминает транспорт курьера
TEST(Courier, WorkMentionsVehicle)
{
    Courier c = makeCourier();
    testing::internal::CaptureStdout();
    c.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Платон") != std::string::npos);
    EXPECT_TRUE(out.find("\"Фургон\"") != std::string::npos);
}

// deliverOrder() печатает сообщение об отправке
TEST(Courier, DeliverOrderPrintsMessage)
{
    Courier c = makeCourier();
    testing::internal::CaptureStdout();
    c.deliverOrder();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("отправился доставлять заказ") != std::string::npos);
}

// Транспорт у разных курьеров разный
TEST(Courier, DifferentVehicles)
{
    Courier a("А", 1, 1, Role("Курьер", 2), "Велосипед");
    testing::internal::CaptureStdout();
    a.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Велосипед") != std::string::npos);
    EXPECT_TRUE(out.find("Фургон") == std::string::npos);
}
