#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include "lab2/exceptions/WarehouseException.hpp"

// Сообщение сохраняется и доступно через what()
TEST(WarehouseException, StoresMessage)
{
    WarehouseException ex("сбой склада");
    EXPECT_STREQ(ex.what(), "сбой склада");
}

// Базовый класс наследуется от std::runtime_error
TEST(WarehouseException, IsRuntimeError)
{
    EXPECT_THROW(throw WarehouseException("x"), std::runtime_error);
    EXPECT_THROW(throw WarehouseException("x"), std::exception);
}

// Копия исключения сохраняет текст
TEST(WarehouseException, CopyKeepsMessage)
{
    WarehouseException a("исходное");
    WarehouseException b(a);
    EXPECT_STREQ(b.what(), "исходное");
}

// Все производные исключения ловятся по базовому типу
TEST(WarehouseException, DerivedCaughtByBase)
{
    bool caught = false;
    try
    {
        throw std::runtime_error("не то");
    }
    catch (const WarehouseException &)
    {
        caught = false;
    }
    catch (const std::runtime_error &)
    {
        caught = true;
    }
    EXPECT_TRUE(caught); // обычный runtime_error базовым WarehouseException не ловится
}
