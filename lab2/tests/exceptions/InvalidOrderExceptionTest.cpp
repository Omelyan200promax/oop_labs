#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/InvalidOrderException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(InvalidOrderException, StoresMessage)
{
    InvalidOrderException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(InvalidOrderException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw InvalidOrderException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(InvalidOrderException, CatchableAsStdException)
{
    EXPECT_THROW(throw InvalidOrderException("ошибка"), std::exception);
    EXPECT_THROW(throw InvalidOrderException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(InvalidOrderException, AcceptsEmptyMessage)
{
    InvalidOrderException ex("");
    EXPECT_STREQ(ex.what(), "");
}
