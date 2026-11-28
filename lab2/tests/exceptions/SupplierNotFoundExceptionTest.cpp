#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/SupplierNotFoundException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(SupplierNotFoundException, StoresMessage)
{
    SupplierNotFoundException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(SupplierNotFoundException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw SupplierNotFoundException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(SupplierNotFoundException, CatchableAsStdException)
{
    EXPECT_THROW(throw SupplierNotFoundException("ошибка"), std::exception);
    EXPECT_THROW(throw SupplierNotFoundException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(SupplierNotFoundException, AcceptsEmptyMessage)
{
    SupplierNotFoundException ex("");
    EXPECT_STREQ(ex.what(), "");
}
