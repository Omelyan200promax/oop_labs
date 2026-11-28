#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/SupplyContract.hpp"

static SupplyContract makeContract()
{
    return SupplyContract(Supplier("ООО Книжный мир", ContactInfo("+375172001122", "info@kmir.by")),
                          CustomDate(1, 1, 2026), CustomDate(31, 12, 2026));
}

// Дата внутри срока — договор активен
TEST(SupplyContract, ActiveInsidePeriod)
{
    EXPECT_TRUE(makeContract().isActive(CustomDate(15, 6, 2026)));
}

// Границы периода включены
TEST(SupplyContract, ActiveOnBoundaries)
{
    SupplyContract c = makeContract();
    EXPECT_TRUE(c.isActive(CustomDate(1, 1, 2026)));
    EXPECT_TRUE(c.isActive(CustomDate(31, 12, 2026)));
}

// До начала договор не действует
TEST(SupplyContract, InactiveBeforeStart)
{
    EXPECT_FALSE(makeContract().isActive(CustomDate(31, 12, 2025)));
}

// После окончания договор не действует
TEST(SupplyContract, InactiveAfterEnd)
{
    EXPECT_FALSE(makeContract().isActive(CustomDate(1, 1, 2027)));
}

// Дата окончания и поставщик доступны
TEST(SupplyContract, GettersWork)
{
    SupplyContract c = makeContract();
    EXPECT_EQ(c.getEndDate().toString(), "31.12.2026");
    Book book = Book("Тест", "1", Author("А", "Б", "В", 1900, 1950), Publisher("П", "Г"), Genre("Ж", "Ж"),
                     Category("К", "К"), Language("Русский", "ru"), CoverType("Мягкая", false),
                     Price(10.0, "BYN"), Dimensions(1, 1, 1), CustomDate(1, 1, 2020), 1);
    c.getSupplier().supplyBooks(book, 4);
    EXPECT_EQ(book.getStockCount(), 5);
}
