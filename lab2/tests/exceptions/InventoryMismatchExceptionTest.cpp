#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/InventoryMismatchException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(InventoryMismatchException, StoresMessage)
{
    InventoryMismatchException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(InventoryMismatchException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw InventoryMismatchException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(InventoryMismatchException, CatchableAsStdException)
{
    EXPECT_THROW(throw InventoryMismatchException("ошибка"), std::exception);
    EXPECT_THROW(throw InventoryMismatchException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(InventoryMismatchException, AcceptsEmptyMessage)
{
    InventoryMismatchException ex("");
    EXPECT_STREQ(ex.what(), "");
}
