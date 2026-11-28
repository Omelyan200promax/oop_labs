#include <gtest/gtest.h>
#include <string>
#include "lab2/warehouse/Warehouse.hpp"

// Склад с двумя секциями: первая на 2 книги, вторая на 3
static Warehouse makeWarehouse()
{
    Warehouse w("Главный склад", Address("Минск", "ул. Складская, 1"), ContactInfo("+375170000000", "sklad@bsuir.by"));
    Section s1("Классика", WarehouseZone("Сухая зона", 2));
    Rack r1(1);
    r1.addShelf(Shelf(1, 2));
    s1.addRack(r1);
    Section s2("Резерв", WarehouseZone("Зона B", 3));
    Rack r2(2);
    r2.addShelf(Shelf(2, 2));
    s2.addRack(r2);
    w.addSection(s1);
    w.addSection(s2);
    return w;
}

// Пустой склад
TEST(Warehouse, EmptyWarehouse)
{
    Warehouse w = makeWarehouse();
    EXPECT_EQ(w.getTotalStored(), 0);
    EXPECT_EQ(w.countBook("A"), 0);
}

// Книги хранятся и считаются
TEST(Warehouse, StoreAndCountBooks)
{
    Warehouse w = makeWarehouse();
    EXPECT_TRUE(w.storeBook(1.0, "A"));
    EXPECT_TRUE(w.storeBook(1.0, "A"));
    EXPECT_TRUE(w.storeBook(1.0, "B"));
    EXPECT_EQ(w.countBook("A"), 2);
    EXPECT_EQ(w.countBook("B"), 1);
    EXPECT_EQ(w.getTotalStored(), 3);
}

// Когда первая секция заполнена, книги идут во вторую; при полном складе — false
TEST(Warehouse, SpillsToNextSectionThenFails)
{
    Warehouse w = makeWarehouse();
    for (int i = 0; i < 5; ++i)
        EXPECT_TRUE(w.storeBook(1.0, "A"));
    EXPECT_FALSE(w.storeBook(1.0, "A"));
    EXPECT_EQ(w.getTotalStored(), 5);
}

// Удаление книги
TEST(Warehouse, RemoveBook)
{
    Warehouse w = makeWarehouse();
    w.storeBook(1.0, "A");
    EXPECT_TRUE(w.removeBook("A"));
    EXPECT_EQ(w.countBook("A"), 0);
    EXPECT_EQ(w.getTotalStored(), 0);
}

// Удаление отсутствующей книги
TEST(Warehouse, RemoveMissingBookReturnsFalse)
{
    Warehouse w = makeWarehouse();
    EXPECT_FALSE(w.removeBook("Z"));
}

// Освободившееся место можно занять снова
TEST(Warehouse, FreedSpaceCanBeReused)
{
    Warehouse w = makeWarehouse();
    for (int i = 0; i < 5; ++i)
        w.storeBook(1.0, "A");
    EXPECT_TRUE(w.removeBook("A"));
    EXPECT_TRUE(w.storeBook(1.0, "B"));
    EXPECT_EQ(w.getTotalStored(), 5);
}

// Вывод структуры содержит все уровни иерархии
TEST(Warehouse, PrintFullStructureContainsAllLevels)
{
    Warehouse w = makeWarehouse();
    w.storeBook(1.0, "Тихий Дон");
    w.storeBook(1.0, "Тихий Дон");
    testing::internal::CaptureStdout();
    w.printFullStructure();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Главный склад") != std::string::npos);
    EXPECT_TRUE(out.find("Секция: Классика") != std::string::npos);
    EXPECT_TRUE(out.find("Сухая зона") != std::string::npos);
    EXPECT_TRUE(out.find("Стеллаж №1") != std::string::npos);
    EXPECT_TRUE(out.find("Полка №1") != std::string::npos);
    EXPECT_TRUE(out.find("Коробка №1") != std::string::npos);
    EXPECT_TRUE(out.find("Тихий Дон x2") != std::string::npos);
}
