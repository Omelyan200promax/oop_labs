#include <gtest/gtest.h>
#include "lab2/warehouse/Shelf.hpp"
#include "lab2/exceptions/CapacityExceededException.hpp"

// Геттеры и пустая полка
TEST(Shelf, NewShelfIsEmpty)
{
    Shelf s(1, 3);
    EXPECT_EQ(s.getId(), 1);
    EXPECT_EQ(s.getMaxBoxes(), 3);
    EXPECT_EQ(s.getBoxCount(), 0);
}

// Коробки добавляются до лимита
TEST(Shelf, AddBoxWithinLimit)
{
    Shelf s(1, 2);
    s.addBox(Box(1, 10.0));
    s.addBox(Box(2, 10.0));
    EXPECT_EQ(s.getBoxCount(), 2);
}

// Превышение лимита коробок — исключение
TEST(Shelf, AddBoxOverLimitThrows)
{
    Shelf s(1, 1);
    s.addBox(Box(1, 10.0));
    EXPECT_THROW(s.addBox(Box(2, 10.0)), CapacityExceededException);
}

// storeBook создаёт новую коробку и увеличивает счётчик id
TEST(Shelf, StoreBookCreatesBoxAndAdvancesId)
{
    Shelf s(1, 2);
    int nextId = 5;
    EXPECT_TRUE(s.storeBook(1.0, "A", nextId));
    EXPECT_EQ(nextId, 6);
    EXPECT_EQ(s.getBoxCount(), 1);
    EXPECT_EQ(s.getBoxes()[0].getId(), 5);
}

// Вторая лёгкая книга кладётся в ту же коробку
TEST(Shelf, StoreBookReusesExistingBox)
{
    Shelf s(1, 2);
    int nextId = 1;
    s.storeBook(1.0, "A", nextId);
    s.storeBook(1.0, "B", nextId);
    EXPECT_EQ(s.getBoxCount(), 1);
    EXPECT_EQ(nextId, 2);
}

// Тяжёлая книга уходит в новую коробку, а при нехватке места — false
TEST(Shelf, StoreBookReturnsFalseWhenFull)
{
    Shelf s(1, 1);
    int nextId = 1;
    EXPECT_TRUE(s.storeBook(Shelf::DEFAULT_BOX_WEIGHT, "Heavy", nextId));
    EXPECT_FALSE(s.storeBook(1.0, "Extra", nextId)); // коробка полна, новую ставить некуда
    EXPECT_EQ(s.getBoxCount(), 1);
}

// Книга тяжелее максимума коробки не может быть размещена
TEST(Shelf, StoreBookTooHeavyForAnyBox)
{
    Shelf s(1, 2);
    int nextId = 1;
    EXPECT_FALSE(s.storeBook(Shelf::DEFAULT_BOX_WEIGHT + 1.0, "Huge", nextId));
    EXPECT_EQ(s.getBoxCount(), 0);
    EXPECT_EQ(nextId, 1);
}

// Подсчёт и удаление
TEST(Shelf, CountAndRemoveBook)
{
    Shelf s(1, 2);
    int nextId = 1;
    s.storeBook(1.0, "A", nextId);
    s.storeBook(1.0, "A", nextId);
    EXPECT_EQ(s.countBook("A"), 2);
    EXPECT_TRUE(s.removeBook("A"));
    EXPECT_EQ(s.countBook("A"), 1);
    EXPECT_FALSE(s.removeBook("Z"));
}
