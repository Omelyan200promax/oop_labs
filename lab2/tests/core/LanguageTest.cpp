#include <gtest/gtest.h>
#include "lab2/core/Language.hpp"

// ISO-код возвращается как передан
TEST(Language, IsoCode)
{
    Language l("Русский", "ru");
    EXPECT_EQ(l.getCode(), "ru");
}

// Разные языки — разные коды
TEST(Language, DifferentLanguages)
{
    EXPECT_NE(Language("Русский", "ru").getCode(), Language("English", "en").getCode());
}
