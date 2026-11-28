#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/InvalidDimensionsException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(InvalidDimensionsException, StoresMessage)
{
    InvalidDimensionsException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(InvalidDimensionsException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw InvalidDimensionsException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(InvalidDimensionsException, CatchableAsStdException)
{
    EXPECT_THROW(throw InvalidDimensionsException("ошибка"), std::exception);
    EXPECT_THROW(throw InvalidDimensionsException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(InvalidDimensionsException, AcceptsEmptyMessage)
{
    InvalidDimensionsException ex("");
    EXPECT_STREQ(ex.what(), "");
}
