#pragma once
#include <string>
#include "lab2/core/Author.hpp"
#include "lab2/core/Publisher.hpp"
#include "lab2/core/Genre.hpp"
#include "lab2/core/Category.hpp"
#include "lab2/core/Language.hpp"
#include "lab2/core/CoverType.hpp"
#include "lab2/common/Price.hpp"
#include "lab2/common/Dimensions.hpp"
#include "lab2/common/CustomDate.hpp"

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

public:
    Book(std::string title, std::string isbn, Author author, Publisher publisher,
         Genre genre, Category category, Language language, CoverType coverType,
         Price price, Dimensions dimensions, CustomDate pubDate, int stock);

    std::string getInfo() const;
    bool isAvailable() const;
    void addStock(int count);
    bool sellCopy();
};