#include <gtest/gtest.h>
#include "lab2/common/Notification.hpp"

// Новое уведомление хранит текст и не прочитано
TEST(Notification, NewIsUnread)
{
    Notification n("Заказ оплачен");
    EXPECT_EQ(n.getMessage(), "Заказ оплачен");
    EXPECT_FALSE(n.isRead());
}

// markAsRead отмечает как прочитанное
TEST(Notification, MarkAsRead)
{
    Notification n("Привет");
    n.markAsRead();
    EXPECT_TRUE(n.isRead());
}

// Повторная отметка безопасна
TEST(Notification, MarkTwiceIsSafe)
{
    Notification n("Привет");
    n.markAsRead();
    n.markAsRead();
    EXPECT_TRUE(n.isRead());
    EXPECT_EQ(n.getMessage(), "Привет");
}
