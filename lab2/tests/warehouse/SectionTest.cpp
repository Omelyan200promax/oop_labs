#include <gtest/gtest.h>
#include "lab2/warehouse/Section.hpp"

// Собирает секцию: 1 стеллаж, 1 полка на maxBoxes коробок, зона на capacity книг
static Section makeSection(int capacity, int maxBoxes = 3)
{
    Section sec("Классика", WarehouseZone("Сухая зона", capacity));
    Rack rack(1);
    rack.addShelf(Shelf(1, maxBoxes));
    sec.addRack(rack);
    return sec;
}

// Геттеры
TEST(Section, Getters)
{
    Section sec = makeSection(10);
    EXPECT_EQ(sec.getName(), "Классика");
    EXPECT_EQ(sec.getZone().getName(), "Сухая зона");
    EXPECT_EQ(sec.getZone().getCapacity(), 10);
    EXPECT_EQ(sec.getRacks().size(), 1u);
    EXPECT_EQ(sec.getStoredCount(), 0);
}

// storeBook увеличивает счётчик
TEST(Section, StoreBookIncrementsCounter)
{
    Section sec = makeSection(10);
    int nextId = 1;
    EXPECT_TRUE(sec.storeBook(1.0, "A", nextId));
    EXPECT_TRUE(sec.storeBook(1.0, "B", nextId));
    EXPECT_EQ(sec.getStoredCount(), 2);
}

// Лимит секции определяется capacity зоны
TEST(Section, ZoneCapacityLimitsStoredBooks)
{
    Section sec = makeSection(2);
    int nextId = 1;
    EXPECT_TRUE(sec.storeBook(1.0, "A", nextId));
    EXPECT_TRUE(sec.storeBook(1.0, "A", nextId));
    EXPECT_FALSE(sec.storeBook(1.0, "A", nextId));
    EXPECT_EQ(sec.getStoredCount(), 2);
}

// Секция без стеллажей ничего не хранит
TEST(Section, NoRacksNoStorage)
{
    Section sec("Пустая", WarehouseZone("Зона", 5));
    int nextId = 1;
    EXPECT_FALSE(sec.storeBook(1.0, "A", nextId));
    EXPECT_EQ(sec.getStoredCount(), 0);
}

// Если не поместилось физически, счётчик не растёт
TEST(Section, PhysicallyFullDoesNotCount)
{
    Section sec = makeSection(100, 1);
    int nextId = 1;
    EXPECT_TRUE(sec.storeBook(Shelf::DEFAULT_BOX_WEIGHT, "A", nextId));
    EXPECT_FALSE(sec.storeBook(1.0, "B", nextId));
    EXPECT_EQ(sec.getStoredCount(), 1);
}

// Удаление уменьшает счётчик, подсчёт работает
TEST(Section, RemoveAndCount)
{
    Section sec = makeSection(10);
    int nextId = 1;
    sec.storeBook(1.0, "A", nextId);
    sec.storeBook(1.0, "A", nextId);
    EXPECT_EQ(sec.countBook("A"), 2);
    EXPECT_TRUE(sec.removeBook("A"));
    EXPECT_EQ(sec.countBook("A"), 1);
    EXPECT_EQ(sec.getStoredCount(), 1);
    EXPECT_FALSE(sec.removeBook("Z"));
    EXPECT_EQ(sec.getStoredCount(), 1);
}
