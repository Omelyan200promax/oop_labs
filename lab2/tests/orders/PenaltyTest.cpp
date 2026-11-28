#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/Penalty.hpp"


// Штраф выводит причину
TEST(Penalty, ApplyPrintsReason)
{
    Penalty p("опоздание", Price(15.0, "BYN"));
    testing::internal::CaptureStdout();
    p.applyPenalty();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Штраф применен") != std::string::npos);
    EXPECT_TRUE(out.find("опоздание") != std::string::npos);
}

// Разные причины — разный вывод
TEST(Penalty, DifferentReasonsDifferentOutput)
{
    Penalty a("брак", Price(1.0, "BYN"));
    Penalty b("прогул", Price(1.0, "BYN"));
    testing::internal::CaptureStdout();
    a.applyPenalty();
    std::string outA = testing::internal::GetCapturedStdout();
    testing::internal::CaptureStdout();
    b.applyPenalty();
    std::string outB = testing::internal::GetCapturedStdout();
    EXPECT_NE(outA, outB);
}

// Штраф заканчивается переводом строки
TEST(Penalty, OutputEndsWithNewline)
{
    Penalty p("x", Price(1.0, "BYN"));
    testing::internal::CaptureStdout();
    p.applyPenalty();
    std::string out = testing::internal::GetCapturedStdout();
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.back(), '\n');
}
