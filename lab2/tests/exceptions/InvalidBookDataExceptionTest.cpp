#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/InvalidBookDataException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(InvalidBookDataException, StoresMessage)
{
    InvalidBookDataException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(InvalidBookDataException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw InvalidBookDataException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(InvalidBookDataException, CatchableAsStdException)
{
    EXPECT_THROW(throw InvalidBookDataException("ошибка"), std::exception);
    EXPECT_THROW(throw InvalidBookDataException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(InvalidBookDataException, AcceptsEmptyMessage)
{
    InvalidBookDataException ex("");
    EXPECT_STREQ(ex.what(), "");
}
