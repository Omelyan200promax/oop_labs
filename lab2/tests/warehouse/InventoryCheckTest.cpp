#include <gtest/gtest.h>
#include "lab2/warehouse/InventoryCheck.hpp"

// Новая инвентаризация не завершена
TEST(InventoryCheck, NotCompletedInitially)
{
    InventoryCheck check(CustomDate(1, 12, 2026));
    EXPECT_FALSE(check.isCompleted());
}

// После complete() помечается завершённой
TEST(InventoryCheck, CompleteMarksAsCompleted)
{
    InventoryCheck check(CustomDate(1, 12, 2026));
    check.complete();
    EXPECT_TRUE(check.isCompleted());
}

// Повторное завершение безопасно
TEST(InventoryCheck, CompleteTwiceStaysCompleted)
{
    InventoryCheck check(CustomDate(1, 12, 2026));
    check.complete();
    check.complete();
    EXPECT_TRUE(check.isCompleted());
}
