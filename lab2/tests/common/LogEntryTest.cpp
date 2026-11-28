#include <gtest/gtest.h>
#include "lab2/common/LogEntry.hpp"

// Действие сохраняется
TEST(LogEntry, StoresAction)
{
    LogEntry e("Вход в систему");
    EXPECT_EQ(e.getAction(), "Вход в систему");
}

// Пустое действие допустимо
TEST(LogEntry, EmptyAction)
{
    LogEntry e("");
    EXPECT_EQ(e.getAction(), "");
}
