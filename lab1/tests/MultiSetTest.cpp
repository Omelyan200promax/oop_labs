#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "lab1/MultiSet.hpp"
#include "lab1/Set.hpp"
#include "lab1/Atom.hpp"

// Вспомогательная функция
static std::shared_ptr<SetElement> atom(const std::string &value)
{
    return std::make_shared<Atom>(value);
}

// Базовые операции

TEST(MultiSetTest, NewMultiSetIsEmpty)
{
    MultiSet ms;
    EXPECT_TRUE(ms.empty());
    EXPECT_EQ(ms.size(), 0);
}

TEST(MultiSetTest, AddIncreasesCount)
{
    MultiSet ms;
    ms.add(atom("a"));
    EXPECT_EQ(ms.count(atom("a")), 1);
    EXPECT_EQ(ms.size(), 1);

    ms.add(atom("a"));
    EXPECT_EQ(ms.count(atom("a")), 2);
    EXPECT_EQ(ms.size(), 2);
}

TEST(MultiSetTest, AddDifferentElements)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("b"));
    EXPECT_EQ(ms.size(), 2);
    EXPECT_EQ(ms.count(atom("a")), 1);
    EXPECT_EQ(ms.count(atom("b")), 1);
}

TEST(MultiSetTest, RemoveDecreasesCount)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.remove(atom("a"));
    EXPECT_EQ(ms.count(atom("a")), 1);
}

TEST(MultiSetTest, RemoveDeletesWhenCountZero)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.remove(atom("a"));
    EXPECT_EQ(ms.count(atom("a")), 0);
    EXPECT_TRUE(ms.empty());
}

TEST(MultiSetTest, ContainsFindsElement)
{
    MultiSet ms;
    ms.add(atom("a"));
    EXPECT_TRUE(ms.contains(atom("a")));
    EXPECT_FALSE(ms.contains(atom("b")));
}

TEST(MultiSetTest, CountReturnsCorrect)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.add(atom("a"));
    EXPECT_EQ(ms.count(atom("a")), 3);
    EXPECT_EQ(ms.count(atom("b")), 0);
}

TEST(MultiSetTest, SizeSumsCounts)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.add(atom("b"));
    EXPECT_EQ(ms.size(), 3);
}

TEST(MultiSetTest, ElementAtReturnsCorrect)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.add(atom("b"));
    EXPECT_TRUE(ms.elementAt(0)->equals(*atom("a")));
    EXPECT_TRUE(ms.elementAt(1)->equals(*atom("a")));
    EXPECT_TRUE(ms.elementAt(2)->equals(*atom("b")));
}

TEST(MultiSetTest, ElementAtOutOfRangeThrows)
{
    MultiSet ms;
    ms.add(atom("a"));
    EXPECT_THROW(ms.elementAt(5), std::out_of_range);
}

// Запрет смешивания

TEST(MultiSetTest, AddSetThrows)
{
    MultiSet ms;
    auto s = std::make_shared<Set>();
    EXPECT_THROW(ms.add(s), std::invalid_argument);
}

// Флаги типа

TEST(MultiSetTest, IsMultiSetReturnsTrue)
{
    MultiSet ms;
    EXPECT_TRUE(ms.isMultiSet());
    EXPECT_FALSE(ms.isPlainSet());
}

// Объединение

TEST(MultiSetTest, UniteTakesMaxCounts)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));

    MultiSet b;
    b.add(atom("x"));
    b.add(atom("x"));
    b.add(atom("x"));
    b.add(atom("y"));

    auto result = a.unite(b);
    auto ms_result = std::dynamic_pointer_cast<MultiSet>(result);
    ASSERT_NE(ms_result, nullptr);
    EXPECT_EQ(ms_result->size(), 4);
    EXPECT_EQ(ms_result->count(atom("x")), 3);
    EXPECT_EQ(ms_result->count(atom("y")), 1);
}

TEST(MultiSetTest, UniteWithSetThrows)
{
    MultiSet a;
    Set s;
    EXPECT_THROW(a.unite(s), std::invalid_argument);
}

// Пересечение

TEST(MultiSetTest, IntersectTakesMinCounts)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    a.add(atom("y"));

    MultiSet b;
    b.add(atom("x"));
    b.add(atom("z"));

    auto result = a.intersect(b);
    auto ms_result = std::dynamic_pointer_cast<MultiSet>(result);
    ASSERT_NE(ms_result, nullptr);
    EXPECT_EQ(ms_result->size(), 1);
    EXPECT_EQ(ms_result->count(atom("x")), 1);
}

TEST(MultiSetTest, IntersectWithSetThrows)
{
    MultiSet a;
    Set s;
    EXPECT_THROW(a.intersect(s), std::invalid_argument);
}

// Разность

TEST(MultiSetTest, DifferenceSubtractsCounts)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    a.add(atom("x"));
    a.add(atom("y"));

    MultiSet b;
    b.add(atom("x"));
    b.add(atom("x"));

    auto result = a.difference(b);
    auto ms_result = std::dynamic_pointer_cast<MultiSet>(result);
    ASSERT_NE(ms_result, nullptr);
    EXPECT_EQ(ms_result->size(), 2);
    EXPECT_EQ(ms_result->count(atom("x")), 1);
    EXPECT_EQ(ms_result->count(atom("y")), 1);
}

TEST(MultiSetTest, DifferenceWithSetThrows)
{
    MultiSet a;
    Set s;
    EXPECT_THROW(a.difference(s), std::invalid_argument);
}

// Операторы +, +=

TEST(MultiSetTest, OperatorPlusEquals)
{
    MultiSet a;
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));
    b.add(atom("y"));
    a += b;
    EXPECT_EQ(a.count(atom("x")), 2);
    EXPECT_EQ(a.count(atom("y")), 1);
}

TEST(MultiSetTest, OperatorPlus)
{
    MultiSet a;
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("y"));
    MultiSet c = a + b;
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(a.size(), 1);
}

// Операторы *, *=

TEST(MultiSetTest, OperatorMultEquals)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    a.add(atom("y"));

    MultiSet b;
    b.add(atom("x"));

    a *= b;
    EXPECT_EQ(a.count(atom("x")), 1);
    EXPECT_EQ(a.count(atom("y")), 0);
}

TEST(MultiSetTest, OperatorMult)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));

    MultiSet c = a * b;
    EXPECT_EQ(c.count(atom("x")), 1);
    EXPECT_EQ(a.count(atom("x")), 2);
}

// Операторы -, -=

TEST(MultiSetTest, OperatorMinusEquals)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));

    a -= b;
    EXPECT_EQ(a.count(atom("x")), 1);
}

TEST(MultiSetTest, OperatorMinus)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));

    MultiSet c = a - b;
    EXPECT_EQ(c.count(atom("x")), 1);
    EXPECT_EQ(a.count(atom("x")), 2);
}

// Оператор []

TEST(MultiSetTest, OperatorIndexReturnsCount)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    EXPECT_EQ(ms[atom("a")], 2);
    EXPECT_EQ(ms[atom("b")], 0);
}

// Сравнение

TEST(MultiSetTest, EqualMultiSets)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));

    MultiSet b;
    b.add(atom("x"));
    b.add(atom("x"));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(MultiSetTest, NotEqualMultiSetsDifferentSize)
{
    MultiSet a;
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));
    b.add(atom("x"));

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(MultiSetTest, NotEqualMultiSetsDifferentCounts)
{
    MultiSet a;
    a.add(atom("x"));
    a.add(atom("x"));
    a.add(atom("y"));

    MultiSet b;
    b.add(atom("x"));
    b.add(atom("y"));
    b.add(atom("y"));

    EXPECT_FALSE(a == b);
}

// equals через SetElement

TEST(MultiSetTest, EqualsViaElementInterface)
{
    MultiSet a;
    a.add(atom("x"));
    MultiSet b;
    b.add(atom("x"));
    EXPECT_TRUE(a.equals(b));
}

TEST(MultiSetTest, EqualsWithDifferentType)
{
    MultiSet ms;
    ms.add(atom("a"));
    EXPECT_FALSE(ms.equals(*atom("a")));
}

// Клонирование

TEST(MultiSetTest, CloneProducesEqualMultiSet)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    auto copy = ms.clone();
    EXPECT_TRUE(ms.equals(*copy));
}

// Вывод

TEST(MultiSetTest, PrintOutputsBraces)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.add(atom("b"));
    std::ostringstream os;
    ms.print(os);
    std::string out = os.str();
    EXPECT_NE(out.find("{"), std::string::npos);
    EXPECT_NE(out.find("}"), std::string::npos);
    EXPECT_NE(out.find("a"), std::string::npos);
}

TEST(MultiSetTest, OperatorOutput)
{
    MultiSet ms;
    ms.add(atom("a"));
    std::ostringstream os;
    os << ms;
    EXPECT_FALSE(os.str().empty());
}

TEST(MultiSetTest, PrintEmptyMultiSet)
{
    MultiSet ms;
    std::ostringstream os;
    ms.print(os);
    EXPECT_EQ(os.str(), "{}");
}

// Булеан

TEST(MultiSetTest, PowerSetOfEmpty)
{
    MultiSet ms;
    auto subsets = ms.powerSet();
    EXPECT_EQ(subsets.size(), 1);
}

TEST(MultiSetTest, PowerSetOfMultiSet)
{
    MultiSet ms;
    ms.add(atom("a"));
    ms.add(atom("a"));
    ms.add(atom("b"));
    auto subsets = ms.powerSet();
    // У 'a' кратность 2 (варианты 0, 1, 2), у 'b' кратность 1 (варианты 0, 1).
    // Всего 3 * 2 = 6 подмножеств.
    EXPECT_EQ(subsets.size(), 6);
}

// Парсинг из строки

TEST(MultiSetTest, FromStringSimple)
{
    MultiSet ms = MultiSet::fromString("{a, b, c}");
    EXPECT_EQ(ms.size(), 3);
    EXPECT_EQ(ms.count(atom("a")), 1);
}

TEST(MultiSetTest, FromStringEmpty)
{
    MultiSet ms = MultiSet::fromString("{}");
    EXPECT_TRUE(ms.empty());
}

TEST(MultiSetTest, FromStringDuplicates)
{
    MultiSet ms = MultiSet::fromString("{a, a, b, a}");
    EXPECT_EQ(ms.count(atom("a")), 3);
    EXPECT_EQ(ms.count(atom("b")), 1);
}

TEST(MultiSetTest, FromStringNested)
{
    MultiSet ms = MultiSet::fromString("{a, {b, b}}");
    EXPECT_EQ(ms.size(), 2);
}

TEST(MultiSetTest, FromStringMissingBraceThrows)
{
    EXPECT_THROW(MultiSet::fromString("a, b, c"), std::invalid_argument);
}