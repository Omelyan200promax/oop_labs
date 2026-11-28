#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Payment.hpp"
#include "lab2/exceptions/InvalidPaymentException.hpp"

// Вспомогательная функция: клиент с заданным балансом
static Customer makeCustomer(double balance)
{
    return Customer("Анна", ContactInfo("+375291112233", "anna@bsuir.by"), Address("Минск", "ул. Козлова, 15"), balance);
}

// Успешная оплата, когда денег хватает
TEST(Payment, SuccessWhenBalanceIsEnough)
{
    Payment p(1, makeCustomer(500.0), Price(200.0, "BYN"));
    EXPECT_FALSE(p.getStatus());
    p.processPayment();
    EXPECT_TRUE(p.getStatus());
}

// Оплата ровно на весь баланс допустима
TEST(Payment, SuccessWhenAmountEqualsBalance)
{
    Payment p(1, makeCustomer(100.0), Price(100.0, "BYN"));
    EXPECT_NO_THROW(p.processPayment());
    EXPECT_TRUE(p.getStatus());
}

// Недостаточно денег — исключение, статус не меняется
TEST(Payment, ThrowsWhenBalanceTooLow)
{
    Payment p(1, makeCustomer(50.0), Price(200.0, "BYN"));
    EXPECT_THROW(p.processPayment(), InvalidPaymentException);
    EXPECT_FALSE(p.getStatus());
}

// Сумма берётся из Price, а не фиксированная
TEST(Payment, UsesRealAmount)
{
    Payment cheap(1, makeCustomer(1500.0), Price(1200.0, "BYN"));
    EXPECT_NO_THROW(cheap.processPayment());
    Payment tiny(2, makeCustomer(10.0), Price(5.0, "BYN"));
    EXPECT_NO_THROW(tiny.processPayment());
}
