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

class Book
{
private:
    std::string title_;
    std::string isbn_;
    Author author_;
    Publisher publisher_;
    Genre genre_;
    Category category_;
    Language language_;
    CoverType coverType_;
    Price price_;
    Dimensions dimensions_;
    CustomDate publicationDate_;
    int stockCount_;
    Rating rating_;
    std::vector<Review> reviews_;

public:
    Book(std::string title, std::string isbn, Author author, Publisher publisher,
         Genre genre, Category category, Language language, CoverType coverType,
         Price price, Dimensions dimensions, CustomDate pubDate, int stock);

    std::string getInfo() const;
    bool isAvailable() const;
    void addStock(int count);
    bool sellCopy();

    // Геттеры
    std::string getTitle() const;
    std::string getIsbn() const;
    std::string getAuthorName() const;
    std::string getGenreName() const;
    double getPriceAmount() const;
    double getWeight() const; // расчётный вес (кг) по габаритам
    int getStockCount() const;
    double getRatingScore() const;
    std::vector<Review> getReviews() const;

    // Методы для отзывов и рейтинга
    void addReview(Review review);
    void addRating(int score);

    // Применяет скидку (в процентах) к цене книги
    void applyDiscount(double percent);
};