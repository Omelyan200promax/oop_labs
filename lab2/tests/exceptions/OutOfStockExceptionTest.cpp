#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/OutOfStockException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(OutOfStockException, StoresMessage)
{
    OutOfStockException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(OutOfStockException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw OutOfStockException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(OutOfStockException, CatchableAsStdException)
{
    EXPECT_THROW(throw OutOfStockException("ошибка"), std::exception);
    EXPECT_THROW(throw OutOfStockException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(OutOfStockException, AcceptsEmptyMessage)
{
    OutOfStockException ex("");
    EXPECT_STREQ(ex.what(), "");
}
