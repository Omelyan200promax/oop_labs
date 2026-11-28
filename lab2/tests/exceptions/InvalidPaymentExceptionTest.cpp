#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/InvalidPaymentException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(InvalidPaymentException, StoresMessage)
{
    InvalidPaymentException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(InvalidPaymentException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw InvalidPaymentException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(InvalidPaymentException, CatchableAsStdException)
{
    EXPECT_THROW(throw InvalidPaymentException("ошибка"), std::exception);
    EXPECT_THROW(throw InvalidPaymentException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(InvalidPaymentException, AcceptsEmptyMessage)
{
    InvalidPaymentException ex("");
    EXPECT_STREQ(ex.what(), "");
}
