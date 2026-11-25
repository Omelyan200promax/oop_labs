#include "lab2/core/Book.hpp"
#include "lab2/exceptions/InvalidBookDataException.hpp"
#include <sstream>

Book::Book(std::string title, std::string isbn, Author author, Publisher publisher,
           Genre genre, Category category, Language language, CoverType coverType,
           Price price, Dimensions dimensions, CustomDate pubDate, int stock)
    : title_(title), isbn_(isbn), author_(author), publisher_(publisher),
      genre_(genre), category_(category), language_(language), coverType_(coverType),
      price_(price), dimensions_(dimensions), publicationDate_(pubDate), stockCount_(stock),
      rating_(0)
{ // Инициализируем рейтинг нулем

    if (title_.empty() || isbn_.empty())
    {
        throw InvalidBookDataException("Название и ISBN не могут быть пустыми");
    }
}

void Book::addReview(Review review) { reviews_.push_back(review); }
void Book::updateRating(int newScore) { rating_ = Rating(newScore); }

std::string Book::getInfo() const
{
    std::ostringstream os;
    os << "Книга: " << title_ << " | Автор: " << author_.getFullName()
       << " | Жанр: " << genre_.getDescription()
       << " | Язык: " << language_.getCode()
       << " | Рейтинг: " << rating_.getScore()
       << " | Цена: " << price_.toString()
       << " | На складе: " << stockCount_ << " шт.";
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

std::string Book::getTitle() const { return title_; }
std::string Book::getAuthorName() const { return author_.getFullName(); }
double Book::getPriceAmount() const { return price_.getAmount(); }
int Book::getStockCount() const { return stockCount_; }
int Book::getRatingScore() const { return rating_.getScore(); }
std::vector<Review> Book::getReviews() const { return reviews_; }