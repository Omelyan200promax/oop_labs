#include <gtest/gtest.h>
#include "lab2/warehouse/Box.hpp"

// Новая коробка пуста
TEST(Box, NewBoxIsEmpty)
{
    Box box(1, 10.0);
    EXPECT_EQ(box.getId(), 1);
    EXPECT_DOUBLE_EQ(box.getMaxWeight(), 10.0);
    EXPECT_DOUBLE_EQ(box.getCurrentWeight(), 0.0);
    EXPECT_TRUE(box.getContents().empty());
}

// Книга кладётся, пока не превышен максимальный вес
TEST(Box, PutBookWithinCapacity)
{
    Box box(1, 10.0);
    EXPECT_TRUE(box.putBook(4.0, "A"));
    EXPECT_TRUE(box.putBook(6.0, "B")); // ровно по лимиту
    EXPECT_DOUBLE_EQ(box.getCurrentWeight(), 10.0);
    EXPECT_EQ(box.getContents().size(), 2u);
}

// Слишком тяжёлая книга не помещается
TEST(Box, PutBookOverweightRejected)
{
    Box box(1, 5.0);
    EXPECT_TRUE(box.putBook(4.0, "A"));
    EXPECT_FALSE(box.putBook(1.5, "B"));
    EXPECT_DOUBLE_EQ(box.getCurrentWeight(), 4.0);
    EXPECT_EQ(box.getContents().size(), 1u);
}

// Подсчёт одинаковых книг
TEST(Box, CountBook)
{
    Box box(1, 10.0);
    box.putBook(1.0, "A");
    box.putBook(1.0, "A");
    box.putBook(1.0, "B");
    EXPECT_EQ(box.countBook("A"), 2);
    EXPECT_EQ(box.countBook("B"), 1);
    EXPECT_EQ(box.countBook("C"), 0);
}

// Удаление уменьшает вес и число книг
TEST(Box, RemoveBookUpdatesWeight)
{
    Box box(1, 10.0);
    box.putBook(2.0, "A");
    box.putBook(3.0, "B");
    EXPECT_TRUE(box.removeBook("A"));
    EXPECT_DOUBLE_EQ(box.getCurrentWeight(), 3.0);
    EXPECT_EQ(box.countBook("A"), 0);
    EXPECT_EQ(box.getContents().size(), 1u);
}

// Удаление отсутствующей книги возвращает false
TEST(Box, RemoveMissingBookReturnsFalse)
{
    Box box(1, 10.0);
    box.putBook(2.0, "A");
    EXPECT_FALSE(box.removeBook("Z"));
    EXPECT_DOUBLE_EQ(box.getCurrentWeight(), 2.0);
}
