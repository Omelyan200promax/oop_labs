#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/AccessDeniedException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(AccessDeniedException, StoresMessage)
{
    AccessDeniedException ex("тестовое сообщение");
    EXPECT_STREQ(ex.what(), "тестовое сообщение");
}

// Исключение можно поймать как базовый WarehouseException
TEST(AccessDeniedException, CatchableAsWarehouseException)
{
    EXPECT_THROW(throw AccessDeniedException("ошибка"), WarehouseException);
}

// ... и как std::exception / std::runtime_error
TEST(AccessDeniedException, CatchableAsStdException)
{
    EXPECT_THROW(throw AccessDeniedException("ошибка"), std::exception);
    EXPECT_THROW(throw AccessDeniedException("ошибка"), std::runtime_error);
}

// Пустое сообщение допустимо
TEST(AccessDeniedException, AcceptsEmptyMessage)
{
    AccessDeniedException ex("");
    EXPECT_STREQ(ex.what(), "");
}
