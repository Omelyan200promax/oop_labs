#include <gtest/gtest.h>
#include "lab2/warehouse/Pallet.hpp"

// Новый паллет пуст
TEST(Pallet, EmptyInitially)
{
    Pallet p(1);
    EXPECT_EQ(p.getBoxCount(), 0);
}

// Добавление коробок увеличивает счётчик
TEST(Pallet, AddBoxIncreasesCount)
{
    Pallet p(1);
    p.addBox(Box(1, 10.0));
    p.addBox(Box(2, 10.0));
    EXPECT_EQ(p.getBoxCount(), 2);
}

// Паллет принимает и пустые, и заполненные коробки
TEST(Pallet, AcceptsFilledBox)
{
    Pallet p(7);
    Box b(3, 5.0);
    b.putBook(1.0, "A");
    p.addBox(b);
    EXPECT_EQ(p.getBoxCount(), 1);
}
