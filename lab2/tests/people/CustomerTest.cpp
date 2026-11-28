#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Customer.hpp"

static Customer makeCustomer(double balance = 100.0)
{
    return Customer("Анна", ContactInfo("+375291234567", "anna@bsuir.by"), Address("Минск", "ул. Козлова, 15"), balance);
}

// Геттеры возвращают переданные данные
TEST(Customer, Getters)
{
    Customer c = makeCustomer(350.0);
    EXPECT_EQ(c.getName(), "Анна");
    EXPECT_EQ(c.getEmail(), "anna@bsuir.by");
    EXPECT_EQ(c.getAddressStr(), c.getAddress().getFullAddress());
    EXPECT_TRUE(c.getAddressStr().find("Минск") != std::string::npos);
    EXPECT_DOUBLE_EQ(c.getBalance(), 350.0);
    EXPECT_EQ(c.getActiveOrdersCount(), 0);
}

// Оплата при достаточном балансе списывает деньги
TEST(Customer, PaySucceedsWhenEnoughMoney)
{
    Customer c = makeCustomer(100.0);
    EXPECT_TRUE(c.pay(40.0));
    EXPECT_DOUBLE_EQ(c.getBalance(), 60.0);
}

// Оплата всей суммы баланса допустима (граница)
TEST(Customer, PayExactBalance)
{
    Customer c = makeCustomer(50.0);
    EXPECT_TRUE(c.pay(50.0));
    EXPECT_DOUBLE_EQ(c.getBalance(), 0.0);
}

// При нехватке средств оплата отклоняется, баланс не меняется
TEST(Customer, PayFailsWhenNotEnoughMoney)
{
    Customer c = makeCustomer(30.0);
    EXPECT_FALSE(c.pay(30.01));
    EXPECT_DOUBLE_EQ(c.getBalance(), 30.0);
}

// Пополнение увеличивает баланс, неположительные суммы игнорируются
TEST(Customer, DepositAddsOnlyPositiveAmounts)
{
    Customer c = makeCustomer(10.0);
    c.deposit(15.5);
    EXPECT_DOUBLE_EQ(c.getBalance(), 25.5);
    c.deposit(0);
    c.deposit(-100);
    EXPECT_DOUBLE_EQ(c.getBalance(), 25.5);
}

// Счётчик активных заказов не уходит ниже нуля
TEST(Customer, ActiveOrdersCounter)
{
    Customer c = makeCustomer();
    c.decrementActiveOrders();
    EXPECT_EQ(c.getActiveOrdersCount(), 0);
    c.incrementActiveOrders();
    c.incrementActiveOrders();
    EXPECT_EQ(c.getActiveOrdersCount(), 2);
    c.decrementActiveOrders();
    EXPECT_EQ(c.getActiveOrdersCount(), 1);
}

// Уведомления добавляются и могут быть помечены прочитанными через ссылку
TEST(Customer, NotificationsStoredAndModifiable)
{
    Customer c = makeCustomer();
    EXPECT_TRUE(c.getNotifications().empty());
    c.addNotification(Notification("Заказ создан"));
    c.addNotification(Notification("Заказ оплачен"));
    ASSERT_EQ(c.getNotifications().size(), 2u);
    EXPECT_FALSE(c.getNotifications()[0].isRead());
    c.getNotifications()[0].markAsRead();
    EXPECT_TRUE(c.getNotifications()[0].isRead());
    EXPECT_FALSE(c.getNotifications()[1].isRead());
    EXPECT_EQ(c.getNotifications()[1].getMessage(), "Заказ оплачен");
}

// Идентификаторы заказов сохраняются в порядке добавления
TEST(Customer, OrderIdsKeptInOrder)
{
    Customer c = makeCustomer();
    EXPECT_TRUE(c.getOrderIds().empty());
    c.addOrderId(5);
    c.addOrderId(9);
    std::vector<int> ids = c.getOrderIds();
    ASSERT_EQ(ids.size(), 2u);
    EXPECT_EQ(ids[0], 5);
    EXPECT_EQ(ids[1], 9);
}
