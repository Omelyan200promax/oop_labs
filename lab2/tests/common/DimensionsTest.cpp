#include <gtest/gtest.h>
#include "lab2/common/Dimensions.hpp"
#include "lab2/exceptions/InvalidDimensionsException.hpp"

// Объём = длина * ширина * высота
TEST(Dimensions, Volume)
{
    Dimensions d(2, 3, 4);
    EXPECT_DOUBLE_EQ(d.getVolume(), 24.0);
}

// Нулевой или отрицательный размер недопустим
TEST(Dimensions, NonPositiveThrows)
{
    EXPECT_THROW(Dimensions(0, 1, 1), InvalidDimensionsException);
    EXPECT_THROW(Dimensions(1, -1, 1), InvalidDimensionsException);
    EXPECT_THROW(Dimensions(1, 1, 0), InvalidDimensionsException);
}

// canFitIn: граница включительно
TEST(Dimensions, CanFitIn)
{
    Dimensions d(2, 3, 4);
    EXPECT_TRUE(d.canFitIn(24.0));
    EXPECT_TRUE(d.canFitIn(100.0));
    EXPECT_FALSE(d.canFitIn(23.9));
}

// Строковое представление "ДxШxВ"
TEST(Dimensions, ToString)
{
    EXPECT_EQ(Dimensions(2, 3, 4).toString(), "2x3x4");
    EXPECT_EQ(Dimensions(1.5, 2, 3).toString(), "1.5x2x3");
}
