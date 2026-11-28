#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Storekeeper.hpp"

static Storekeeper makeKeeper()
{
    return Storekeeper("Никита", 2, 1800.0, Role("Кладовщик", 3), "Ночная");
}

// Унаследованные геттеры
TEST(Storekeeper, InheritedGetters)
{
    Storekeeper s = makeKeeper();
    EXPECT_EQ(s.getName(), "Никита");
    EXPECT_DOUBLE_EQ(s.getSalary(), 1800.0);
    EXPECT_EQ(s.getRole().getTitle(), "Кладовщик");
}

// work() упоминает смену
TEST(Storekeeper, WorkMentionsShift)
{
    Storekeeper s = makeKeeper();
    testing::internal::CaptureStdout();
    s.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("принимает товар в смену \"Ночная\"") != std::string::npos);
}

// sortBooks() сообщает о раскладке книг
TEST(Storekeeper, SortBooksPrintsMessage)
{
    Storekeeper s = makeKeeper();
    testing::internal::CaptureStdout();
    s.sortBooks();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Никита") != std::string::npos);
    EXPECT_TRUE(out.find("раскладывает книги") != std::string::npos);
}

// Смена зависит от объекта
TEST(Storekeeper, DifferentShifts)
{
    Storekeeper s("Анна", 9, 1, Role("Кладовщик", 3), "Дневная");
    testing::internal::CaptureStdout();
    s.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Дневная") != std::string::npos);
}
