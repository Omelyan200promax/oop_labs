#include "lab2/core/Book.hpp"
#include "lab2/exceptions/InvalidBookDataException.hpp"
#include <sstream>

Book::Book(std::string title, std::string isbn, Author author, Publisher publisher, Genre genre, Price price, Dimensions dimensions, CustomDate pubDate, int stock)
    : title_(title), isbn_(isbn), author_(author), publisher_(publisher), genre_(genre), price_(price), dimensions_(dimensions), publicationDate_(pubDate), stockCount_(stock)
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
       << " | Жанр: " << genre_.getDescription() << " | Цена: " << price_.toString()
       << " | На складе: " << stockCount_ << " шт.";
    return os.str();
}

bool Book::isAvailable() const
{
    return stockCount_ > 0;
}

void Book::addStock(int count)
{
    if (count > 0)
    {
        stockCount_ += count;
    }
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
