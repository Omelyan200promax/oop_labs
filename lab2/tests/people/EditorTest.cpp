#include <gtest/gtest.h>
#include <string>
#include "lab2/people/Editor.hpp"

static Editor makeEditor()
{
    return Editor("Мария", 6, 1900.0, Role("Редактор", 3), 7);
}

// Унаследованные геттеры
TEST(Editor, InheritedGetters)
{
    Editor e = makeEditor();
    EXPECT_EQ(e.getName(), "Мария");
    EXPECT_DOUBLE_EQ(e.getSalary(), 1900.0);
    EXPECT_EQ(e.getRole().getAccessLevel(), 3);
}

// work() печатает сообщение о редактировании текста
TEST(Editor, WorkPrintsMessage)
{
    Editor e = makeEditor();
    testing::internal::CaptureStdout();
    e.work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Мария") != std::string::npos);
    EXPECT_TRUE(out.find("редактирует текст") != std::string::npos);
}

// editBook() печатает сообщение о редактировании описания
TEST(Editor, EditBookPrintsMessage)
{
    Editor e = makeEditor();
    testing::internal::CaptureStdout();
    e.editBook();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("редактирует описание книги") != std::string::npos);
}

// Через указатель на базовый класс вызывается work() редактора
TEST(Editor, PolymorphicWork)
{
    Editor e = makeEditor();
    Employee *p = &e;
    testing::internal::CaptureStdout();
    p->work();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("редактирует текст") != std::string::npos);
}
