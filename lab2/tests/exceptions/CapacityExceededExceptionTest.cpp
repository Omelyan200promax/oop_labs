#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/CapacityExceededException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(CapacityExceededException, StoresMessage)
{
    CapacityExceededException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(CapacityExceededException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw CapacityExceededException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(CapacityExceededException, CatchableAsStdException)
{
    EXPECT_THROW(throw CapacityExceededException("ошибка"), std::exception);
    EXPECT_THROW(throw CapacityExceededException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(CapacityExceededException, AcceptsEmptyMessage)
{
    CapacityExceededException ex("");
    EXPECT_STREQ(ex.what(), "");
}
