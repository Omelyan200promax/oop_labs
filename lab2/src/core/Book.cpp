#include "lab2/core/Book.hpp"
#include "lab2/exceptions/InvalidBookDataException.hpp"
#include <sstream>

Book::Book(std::string title, std::string isbn, Author author, Publisher publisher,
           Genre genre, Category category, Language language, CoverType coverType,
           Price price, Dimensions dimensions, CustomDate pubDate, int stock)
    : title_(title), isbn_(isbn), author_(author), publisher_(publisher),
      genre_(genre), category_(category), language_(language), coverType_(coverType),
      price_(price), dimensions_(dimensions), publicationDate_(pubDate), stockCount_(stock)
{

    if (title_.empty() || isbn_.empty())
    {
        throw InvalidBookDataException("Название и ISBN не могут быть пустыми");
    }
}

std::string Book::getInfo() const
{
    std::ostringstream os;
    os << "Книга: " << title_ << " | Автор: " << author_.getFullName()
       << " | Жанр: " << genre_.getName();
    return os.str();
}

bool Book::isAvailable() const { return stockCount_ > 0; }
void Book::addStock(int count)
{
    if (count > 0)
        stockCount_ += count;
}
bool Book::sellCopy()
{
    if (isAvailable())
    {
        stockCount_--;
        return true;
    }
    return false;
}

// Геттеры
std::string Book::getTitle() const { return title_; }
std::string Book::getIsbn() const { return isbn_; }
std::string Book::getAuthorName() const { return author_.getFullName(); }
std::string Book::getGenreName() const { return genre_.getName(); }
double Book::getPriceAmount() const { return price_.getAmount(); }

// Грубая оценка: 0.2 кг обложка + 0.4 г на каждый см^3 объёма
double Book::getWeight() const { return 0.2 + dimensions_.getVolume() * 0.0004; }
int Book::getStockCount() const { return stockCount_; }
std::vector<Review> Book::getReviews() const { return reviews_; }

// Работа с рейтингом
double Book::getRatingScore() const
{
    return rating_.getScore();
}

void Book::addReview(Review review)
{
    reviews_.push_back(review);
}

void Book::applyDiscount(double percent) { price_.applyDiscount(percent); }

void Book::addRating(int score)
{
    rating_.addScore(score);
}