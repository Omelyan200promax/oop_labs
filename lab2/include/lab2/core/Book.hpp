/**
 * @file Book.hpp
 * @brief Класс Book — книга в каталоге и на складе.
 */
#pragma once
#include <string>
#include <vector>
#include "lab2/core/Author.hpp"
#include "lab2/core/Publisher.hpp"
#include "lab2/core/Genre.hpp"
#include "lab2/core/Category.hpp"
#include "lab2/core/Language.hpp"
#include "lab2/core/CoverType.hpp"
#include "lab2/common/Price.hpp"
#include "lab2/common/Dimensions.hpp"
#include "lab2/common/CustomDate.hpp"
#include "lab2/common/Review.hpp"
#include "lab2/common/Rating.hpp"

/**
 * @brief Книга: основная единица каталога и складского учёта.
 * @details Объединяет данные об издании (автор, издатель, жанр, язык, обложка, габариты), цену, остаток в учёте, рейтинг и отзывы.
 */
class Book
{
private:
    std::string title_; /**< Название. */
    std::string isbn_; /**< ISBN. */
    Author author_; /**< Автор. */
    Publisher publisher_; /**< Издатель. */
    Genre genre_; /**< Жанр. */
    Category category_; /**< Категория. */
    Language language_; /**< Язык издания. */
    CoverType coverType_; /**< Тип обложки. */
    Price price_; /**< Текущая цена. */
    Dimensions dimensions_; /**< Габариты. */
    CustomDate publicationDate_; /**< Дата издания. */
    int stockCount_; /**< Остаток в учёте, шт. */
    Rating rating_; /**< Рейтинг. */
    std::vector<Review> reviews_; /**< Отзывы читателей. */

public:
    /**
     * @brief Создаёт книгу.
     * @param title Название.
     * @param isbn ISBN.
     * @param author Автор.
     * @param publisher Издатель.
     * @param genre Жанр.
     * @param category Категория.
     * @param language Язык.
     * @param coverType Тип обложки.
     * @param price Цена.
     * @param dimensions Габариты.
     * @param pubDate Дата издания.
     * @param stock Начальный остаток, шт.
     * @throws InvalidBookDataException Если название или ISBN пустые.
     */
    Book(std::string title, std::string isbn, Author author, Publisher publisher,
         Genre genre, Category category, Language language, CoverType coverType,
         Price price, Dimensions dimensions, CustomDate pubDate, int stock);

    /**
     * @brief Краткая информация о книге.
     * @return Строка «Книга: … | Автор: … | Жанр: …».
     */
    std::string getInfo() const;
    /**
     * @brief Проверяет наличие.
     * @return true, если остаток больше нуля.
     */
    bool isAvailable() const;
    /**
     * @brief Увеличивает остаток.
     * @details Неположительное количество игнорируется.
     * @param count Сколько экземпляров добавить.
     */
    void addStock(int count);
    /**
     * @brief Списывает один экземпляр с остатка.
     * @return true, если экземпляр был в наличии и списан; false, если остаток нулевой.
     */
    bool sellCopy();

    // Геттеры
    /**
     * @brief Название.
     * @return Название книги.
     */
    std::string getTitle() const;
    /**
     * @brief ISBN.
     * @return ISBN книги.
     */
    std::string getIsbn() const;
    /**
     * @brief Имя автора.
     * @return Имя и фамилия автора.
     */
    std::string getAuthorName() const;
    /**
     * @brief Название жанра.
     * @return Жанр.
     */
    std::string getGenreName() const;
    /**
     * @brief Текущая цена.
     * @return Сумма цены (без валюты).
     */
    double getPriceAmount() const;
    /**
     * @brief Расчётный вес книги.
     * @details Грубая оценка: 0,2 кг на обложку плюс 0,4 г на каждый см³ объёма.
     * @return Вес, кг.
     */
    double getWeight() const; // расчётный вес (кг) по габаритам
    /**
     * @brief Остаток в учёте.
     * @return Количество экземпляров.
     */
    int getStockCount() const;
    /**
     * @brief Средняя оценка.
     * @return Рейтинг от 1 до 5 или 0, если оценок нет.
     */
    double getRatingScore() const;
    /**
     * @brief Отзывы.
     * @return Копия списка отзывов.
     */
    std::vector<Review> getReviews() const;

    // Методы для отзывов и рейтинга
    /**
     * @brief Добавляет отзыв.
     * @param review Отзыв.
     */
    void addReview(Review review);
    /**
     * @brief Добавляет оценку в рейтинг.
     * @param score Оценка от 1 до 5; значения вне диапазона игнорируются.
     */
    void addRating(int score);

    // Применяет скидку (в процентах) к цене книги
    /**
     * @brief Применяет скидку к цене книги.
     * @param percent Размер скидки, % (допустимо (0; 100]).
     */
    void applyDiscount(double percent);
};