#include <gtest/gtest.h>
#include <sstream>
#include "lab1/Atom.hpp"

// Конструктор и геттер

TEST(AtomTest, StoresValue)
{
    Atom atom("hello");
    EXPECT_EQ(atom.value(), "hello");
}

TEST(AtomTest, EmptyValue)
{
    Atom atom("");
    EXPECT_EQ(atom.value(), "");
}

// equals

TEST(AtomTest, EqualAtomsAreEqual)
{
    Atom a("abc");
    Atom b("abc");
    EXPECT_TRUE(a.equals(b));
}

TEST(AtomTest, DifferentAtomsAreNotEqual)
{
    Atom a("abc");
    Atom b("xyz");
    EXPECT_FALSE(a.equals(b));
}

TEST(AtomTest, NotEqualToDifferentType)
{
    Atom a("abc");
    EXPECT_TRUE(a.equals(a));
}

// clone

TEST(AtomTest, CloneReturnsEqualAtom)
{
    Atom original("value");
    auto copy = original.clone();
    EXPECT_TRUE(original.equals(*copy));
}

TEST(AtomTest, CloneIsIndependent)
{
    Atom original("value");
    auto copy = original.clone();
    EXPECT_NE(&original, copy.get());
}

// print

TEST(AtomTest, PrintOutputsValue)
{
    Atom atom("hello");
    std::ostringstream os;
    atom.print(os);
    EXPECT_EQ(os.str(), "hello");
}
