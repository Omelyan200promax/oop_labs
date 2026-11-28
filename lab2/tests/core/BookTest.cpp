#include <gtest/gtest.h>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/exceptions/InvalidBookDataException.hpp"

// Вспомогательная функция: книга с заданными названием, ISBN и остатком
static Book makeBook(const std::string &title = "Война и мир", const std::string &isbn = "978-1", int stock = 3)
{
    return Book(title, isbn, Author("Лев", "Толстой", "Россия", 1828, 1910),
                Publisher("Азбука", "СПб"), Genre("Роман", "Проза"), Category("Классика", "Классика"),
                Language("Русский", "ru"), CoverType("Твердая", true), Price(100.0, "BYN"),
                Dimensions(10, 10, 10), CustomDate(1, 1, 2020), stock);
}

// Геттеры возвращают переданные данные
TEST(Book, Getters)
{
    Book b = makeBook();
    EXPECT_EQ(b.getTitle(), "Война и мир");
    EXPECT_EQ(b.getIsbn(), "978-1");
    EXPECT_EQ(b.getAuthorName(), "Лев Толстой");
    EXPECT_EQ(b.getGenreName(), "Роман");
    EXPECT_DOUBLE_EQ(b.getPriceAmount(), 100.0);
    EXPECT_EQ(b.getStockCount(), 3);
}

// Пустое название или ISBN недопустимы
TEST(Book, EmptyTitleOrIsbnThrows)
{
    EXPECT_THROW(makeBook("", "978-1"), InvalidBookDataException);
    EXPECT_THROW(makeBook("Название", ""), InvalidBookDataException);
}

// Краткая информация о книге
TEST(Book, GetInfo)
{
    Book b = makeBook();
    EXPECT_EQ(b.getInfo(), "Книга: Война и мир | Автор: Лев Толстой | Жанр: Роман");
}

// Доступность зависит от остатка
TEST(Book, Availability)
{
    EXPECT_TRUE(makeBook("A", "1", 1).isAvailable());
    EXPECT_FALSE(makeBook("A", "1", 0).isAvailable());
}

// Продажа уменьшает остаток; при нуле продажа невозможна
TEST(Book, SellCopy)
{
    Book b = makeBook("A", "1", 1);
    EXPECT_TRUE(b.sellCopy());
    EXPECT_EQ(b.getStockCount(), 0);
    EXPECT_FALSE(b.sellCopy());
    EXPECT_EQ(b.getStockCount(), 0);
}

// Пополнение остатка: положительные значения добавляются, остальные игнорируются
TEST(Book, AddStock)
{
    Book b = makeBook("A", "1", 2);
    b.addStock(5);
    EXPECT_EQ(b.getStockCount(), 7);
    b.addStock(0);
    b.addStock(-4);
    EXPECT_EQ(b.getStockCount(), 7);
}

// Рейтинг: среднее оценок, некорректные игнорируются
TEST(Book, Rating)
{
    Book b = makeBook();
    EXPECT_DOUBLE_EQ(b.getRatingScore(), 0.0);
    b.addRating(5);
    b.addRating(3);
    b.addRating(9);
    EXPECT_DOUBLE_EQ(b.getRatingScore(), 4.0);
}

// Отзывы сохраняются по порядку
TEST(Book, Reviews)
{
    Book b = makeBook();
    EXPECT_TRUE(b.getReviews().empty());
    b.addReview(Review("Хорошо", "Анна"));
    b.addReview(Review("Отлично", "Олег"));
    ASSERT_EQ(b.getReviews().size(), 2u);
    EXPECT_EQ(b.getReviews()[0].getText(), "Хорошо");
    EXPECT_EQ(b.getReviews()[1].getAuthor(), "Олег");
}

// Скидка меняет цену
TEST(Book, ApplyDiscount)
{
    Book b = makeBook();
    b.applyDiscount(10);
    EXPECT_DOUBLE_EQ(b.getPriceAmount(), 90.0);
}

// Вес: 0.2 кг + 0.4 г на см^3 (объём 1000 -> 0.6 кг)
TEST(Book, Weight)
{
    Book b = makeBook();
    EXPECT_NEAR(b.getWeight(), 0.6, 1e-9);
}
