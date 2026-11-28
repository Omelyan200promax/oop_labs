#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/DeliveryFailedException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(DeliveryFailedException, StoresMessage)
{
    DeliveryFailedException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(DeliveryFailedException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw DeliveryFailedException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(DeliveryFailedException, CatchableAsStdException)
{
    EXPECT_THROW(throw DeliveryFailedException("ошибка"), std::exception);
    EXPECT_THROW(throw DeliveryFailedException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(DeliveryFailedException, AcceptsEmptyMessage)
{
    DeliveryFailedException ex("");
    EXPECT_STREQ(ex.what(), "");
}
