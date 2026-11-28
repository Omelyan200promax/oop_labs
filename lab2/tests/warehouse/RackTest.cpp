#include <gtest/gtest.h>
#include "lab2/warehouse/Rack.hpp"

// Новый стеллаж без полок
TEST(Rack, NewRackHasNoShelves)
{
    Rack r(4);
    EXPECT_EQ(r.getId(), 4);
    EXPECT_EQ(r.getShelfCount(), 0);
}

// Полки добавляются
TEST(Rack, AddShelf)
{
    Rack r(1);
    r.addShelf(Shelf(1, 2));
    r.addShelf(Shelf(2, 2));
    EXPECT_EQ(r.getShelfCount(), 2);
    EXPECT_EQ(r.getShelves()[1].getId(), 2);
}

// Без полок хранить негде
TEST(Rack, StoreBookWithoutShelvesFails)
{
    Rack r(1);
    int nextId = 1;
    EXPECT_FALSE(r.storeBook(1.0, "A", nextId));
}

// Когда первая полка заполнена, книга уходит на следующую
TEST(Rack, StoreBookSpillsToNextShelf)
{
    Rack r(1);
    r.addShelf(Shelf(1, 1));
    r.addShelf(Shelf(2, 1));
    int nextId = 1;
    EXPECT_TRUE(r.storeBook(Shelf::DEFAULT_BOX_WEIGHT, "A", nextId));
    EXPECT_TRUE(r.storeBook(1.0, "B", nextId));
    EXPECT_EQ(r.getShelves()[0].getBoxCount(), 1);
    EXPECT_EQ(r.getShelves()[1].getBoxCount(), 1);
}

// Подсчёт и удаление по всем полкам
TEST(Rack, CountAndRemoveAcrossShelves)
{
    Rack r(1);
    r.addShelf(Shelf(1, 1));
    r.addShelf(Shelf(2, 1));
    int nextId = 1;
    r.storeBook(Shelf::DEFAULT_BOX_WEIGHT, "A", nextId);
    r.storeBook(1.0, "A", nextId);
    EXPECT_EQ(r.countBook("A"), 2);
    EXPECT_TRUE(r.removeBook("A"));
    EXPECT_EQ(r.countBook("A"), 1);
    EXPECT_FALSE(r.removeBook("Z"));
}
