#include <gtest/gtest.h>
#include "lab2/core/CoverType.hpp"

// Твёрдый переплёт
TEST(CoverType, HardCover)
{
    CoverType c("Твердая", true);
    EXPECT_TRUE(c.isHardCover());
}

// Мягкий переплёт
TEST(CoverType, SoftCover)
{
    CoverType c("Мягкая", false);
    EXPECT_FALSE(c.isHardCover());
}
