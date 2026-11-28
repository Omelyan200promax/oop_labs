#include <gtest/gtest.h>
#include "lab2/common/Report.hpp"

// Заголовок сохраняется, содержимое изначально пустое
TEST(Report, TitleAndEmptyContent)
{
    Report r("Отчёт");
    EXPECT_EQ(r.getTitle(), "Отчёт");
    EXPECT_EQ(r.getContent(), "");
}

// setContent меняет содержимое
TEST(Report, SetContent)
{
    Report r("Отчёт");
    r.setContent("Продано 10 книг");
    EXPECT_EQ(r.getContent(), "Продано 10 книг");
}

// Повторная установка перезаписывает содержимое
TEST(Report, SetContentOverwrites)
{
    Report r("Отчёт");
    r.setContent("a");
    r.setContent("b");
    EXPECT_EQ(r.getContent(), "b");
    EXPECT_EQ(r.getTitle(), "Отчёт");
}
