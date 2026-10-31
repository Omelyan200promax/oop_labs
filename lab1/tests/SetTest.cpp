#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "lab1/Set.hpp"
#include "lab1/Atom.hpp"
#include "lab1/MultiSet.hpp"

// Вспомогательная функция — сделать атом
static std::shared_ptr<SetElement> atom(const std::string &value)
{
    return std::make_shared<Atom>(value);
}

// Конструктор и базовые операции

TEST(SetTest, NewSetIsEmpty)
{
    Set s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, AddIncreasesSize)
{
    Set s;
    s.add(atom("a"));
    EXPECT_EQ(s.size(), 1);
    EXPECT_FALSE(s.empty());
}

TEST(SetTest, AddDuplicateIgnored)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("a"));
    EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, AddMultipleElements)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    s.add(atom("c"));
    EXPECT_EQ(s.size(), 3);
}

TEST(SetTest, RemoveDecreasesSize)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    s.remove(atom("a"));
    EXPECT_EQ(s.size(), 1);
    EXPECT_FALSE(s.contains(atom("a")));
    EXPECT_TRUE(s.contains(atom("b")));
}

TEST(SetTest, RemoveMissingDoesNothing)
{
    Set s;
    s.add(atom("a"));
    s.remove(atom("x"));
    EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, ContainsFindsElement)
{
    Set s;
    s.add(atom("a"));
    EXPECT_TRUE(s.contains(atom("a")));
    EXPECT_FALSE(s.contains(atom("b")));
}

TEST(SetTest, ElementAtReturnsCorrect)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    EXPECT_EQ(s.elementAt(0)->equals(*atom("a")), true);
    EXPECT_EQ(s.elementAt(1)->equals(*atom("b")), true);
}

TEST(SetTest, ElementAtOutOfRangeThrows)
{
    Set s;
    s.add(atom("a"));
    EXPECT_THROW(s.elementAt(5), std::out_of_range);
}

// Запрет смешивания

TEST(SetTest, AddMultiSetThrows)
{
    Set s;
    auto ms = std::make_shared<MultiSet>();
    EXPECT_THROW(s.add(ms), std::invalid_argument);
}

// isPlainSet / isMultiSet

TEST(SetTest, IsPlainSetReturnsTrue)
{
    Set s;
    EXPECT_TRUE(s.isPlainSet());
    EXPECT_FALSE(s.isMultiSet());
}

// Объединение

TEST(SetTest, UniteCombinesElements)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));

    Set b;
    b.add(atom("b"));
    b.add(atom("c"));

    auto result = a.unite(b);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(result->contains(atom("a")));
    EXPECT_TRUE(result->contains(atom("b")));
    EXPECT_TRUE(result->contains(atom("c")));
}

TEST(SetTest, UniteWithMultiSetThrows)
{
    Set a;
    MultiSet ms;
    EXPECT_THROW(a.unite(ms), std::invalid_argument);
}

// Пересечение

TEST(SetTest, IntersectKeepsCommon)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));

    Set b;
    b.add(atom("b"));
    b.add(atom("c"));

    auto result = a.intersect(b);
    EXPECT_EQ(result->size(), 1);
    EXPECT_TRUE(result->contains(atom("b")));
}

TEST(SetTest, IntersectWithMultiSetThrows)
{
    Set a;
    MultiSet ms;
    EXPECT_THROW(a.intersect(ms), std::invalid_argument);
}

// Разность

TEST(SetTest, DifferenceRemovesCommon)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));

    Set b;
    b.add(atom("b"));
    b.add(atom("c"));

    auto result = a.difference(b);
    EXPECT_EQ(result->size(), 1);
    EXPECT_TRUE(result->contains(atom("a")));
    EXPECT_FALSE(result->contains(atom("b")));
}

TEST(SetTest, DifferenceWithMultiSetThrows)
{
    Set a;
    MultiSet ms;
    EXPECT_THROW(a.difference(ms), std::invalid_argument);
}

// Операторы +, +=

TEST(SetTest, OperatorPlusEquals)
{
    Set a;
    a.add(atom("a"));
    Set b;
    b.add(atom("b"));
    a += b;
    EXPECT_EQ(a.size(), 2);
}

TEST(SetTest, OperatorPlus)
{
    Set a;
    a.add(atom("a"));
    Set b;
    b.add(atom("b"));
    Set c = a + b;
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(a.size(), 1);
}

// Операторы *, *=

TEST(SetTest, OperatorMultEquals)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));
    Set b;
    b.add(atom("b"));
    a *= b;
    EXPECT_EQ(a.size(), 1);
    EXPECT_TRUE(a.contains(atom("b")));
}

TEST(SetTest, OperatorMult)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));
    Set b;
    b.add(atom("b"));
    Set c = a * b;
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(a.size(), 2);
}

// Операторы -, -=

TEST(SetTest, OperatorMinusEquals)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));
    Set b;
    b.add(atom("a"));
    a -= b;
    EXPECT_EQ(a.size(), 1);
    EXPECT_TRUE(a.contains(atom("b")));
}

TEST(SetTest, OperatorMinus)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));
    Set b;
    b.add(atom("a"));
    Set c = a - b;
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(a.size(), 2);
}

// Оператор []

TEST(SetTest, OperatorIndexChecksMembership)
{
    Set s;
    s.add(atom("a"));
    EXPECT_TRUE(s[atom("a")]);
    EXPECT_FALSE(s[atom("b")]);
}

// Сравнение

TEST(SetTest, EqualSets)
{
    Set a;
    a.add(atom("a"));
    a.add(atom("b"));

    Set b;
    b.add(atom("a"));
    b.add(atom("b"));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(SetTest, NotEqualSetsDifferentSize)
{
    Set a;
    a.add(atom("a"));

    Set b;
    b.add(atom("a"));
    b.add(atom("b"));

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(SetTest, NotEqualSetsDifferentElements)
{
    Set a;
    a.add(atom("a"));

    Set b;
    b.add(atom("b"));

    EXPECT_FALSE(a == b);
}

// equals через SetElement

TEST(SetTest, EqualsViaElementInterface)
{
    Set a;
    a.add(atom("a"));

    Set b;
    b.add(atom("a"));

    EXPECT_TRUE(a.equals(b));
}

TEST(SetTest, EqualsWithDifferentType)
{
    Set s;
    s.add(atom("a"));
    EXPECT_FALSE(s.equals(*atom("a")));
}

// Клонирование

TEST(SetTest, CloneProducesEqualSet)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    auto copy = s.clone();
    EXPECT_TRUE(s.equals(*copy));
}

// Вывод

TEST(SetTest, PrintOutputsBraces)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    std::ostringstream os;
    s.print(os);
    std::string out = os.str();
    EXPECT_NE(out.find("{"), std::string::npos);
    EXPECT_NE(out.find("}"), std::string::npos);
}

TEST(SetTest, OperatorOutput)
{
    Set s;
    s.add(atom("a"));
    std::ostringstream os;
    os << s;
    EXPECT_FALSE(os.str().empty());
}

TEST(SetTest, PrintEmptySet)
{
    Set s;
    std::ostringstream os;
    s.print(os);
    EXPECT_EQ(os.str(), "{}");
}

// Булеан

TEST(SetTest, PowerSetOfEmpty)
{
    Set s;
    auto subsets = s.powerSet();
    EXPECT_EQ(subsets.size(), 1);
}

TEST(SetTest, PowerSetOfThreeElements)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    s.add(atom("c"));
    auto subsets = s.powerSet();
    EXPECT_EQ(subsets.size(), 8);
}

TEST(SetTest, PowerSetOfTwoElements)
{
    Set s;
    s.add(atom("a"));
    s.add(atom("b"));
    auto subsets = s.powerSet();
    EXPECT_EQ(subsets.size(), 4);
}

// Парсинг из строки

TEST(SetTest, FromStringSimple)
{
    Set s = Set::fromString("{a, b, c}");
    EXPECT_EQ(s.size(), 3);
    EXPECT_TRUE(s.contains(atom("a")));
    EXPECT_TRUE(s.contains(atom("b")));
    EXPECT_TRUE(s.contains(atom("c")));
}

TEST(SetTest, FromStringEmpty)
{
    Set s = Set::fromString("{}");
    EXPECT_TRUE(s.empty());
}

TEST(SetTest, FromStringDuplicatesIgnored)
{
    Set s = Set::fromString("{a, a, b}");
    EXPECT_EQ(s.size(), 2);
}

TEST(SetTest, FromStringNested)
{
    Set s = Set::fromString("{a, {b, c}}");
    EXPECT_EQ(s.size(), 2);
}

TEST(SetTest, FromStringMissingBraceThrows)
{
    EXPECT_THROW(Set::fromString("a, b, c"), std::invalid_argument);
}