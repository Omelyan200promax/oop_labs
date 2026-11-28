#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/BookNotFoundException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(BookNotFoundException, StoresMessage)
{
    BookNotFoundException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(BookNotFoundException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw BookNotFoundException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(BookNotFoundException, CatchableAsStdException)
{
    EXPECT_THROW(throw BookNotFoundException("ошибка"), std::exception);
    EXPECT_THROW(throw BookNotFoundException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(BookNotFoundException, AcceptsEmptyMessage)
{
    BookNotFoundException ex("");
    EXPECT_STREQ(ex.what(), "");
}
