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
#include "lab2/common/Review.hpp" // Новая связь
#include "lab2/common/Rating.hpp" // Новая связь

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
    Rating rating_;               // Новая связь
    std::vector<Review> reviews_; // Новая связь

public:
    Book(std::string title, std::string isbn, Author author, Publisher publisher,
         Genre genre, Category category, Language language, CoverType coverType,
         Price price, Dimensions dimensions, CustomDate pubDate, int stock);

    void addReview(Review review);
    void updateRating(int newScore);
    std::string getInfo() const;
    bool isAvailable() const;
    void addStock(int count);
    bool sellCopy();

    std::string getTitle() const;
    std::string getAuthorName() const;
    double getPriceAmount() const;
    int getStockCount() const;
    int getRatingScore() const;
    std::vector<Review> getReviews() const;
};