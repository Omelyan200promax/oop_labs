#include "lab2/warehouse/Box.hpp"

Box::Box(int id, double maxWeight) : id_(id), maxWeight_(maxWeight), currentWeight_(0) {}

bool Box::putBook(double weight, const std::string &title)
{
    if (currentWeight_ + weight <= maxWeight_)
    {
        currentWeight_ += weight;
        bookTitles_.push_back(title);
        bookWeights_.push_back(weight);
        return true;
    }
    return false;
}

bool Box::removeBook(const std::string &title)
{
    for (size_t i = 0; i < bookTitles_.size(); ++i)
    {
        if (bookTitles_[i] == title)
        {
            currentWeight_ -= bookWeights_[i];
            bookTitles_.erase(bookTitles_.begin() + i);
            bookWeights_.erase(bookWeights_.begin() + i);
            return true;
        }
    }
    return false;
}

int Box::countBook(const std::string &title) const
{
    int n = 0;
    for (const auto &t : bookTitles_)
        if (t == title)
            ++n;
    return n;
}

int Box::getId() const { return id_; }
double Box::getCurrentWeight() const { return currentWeight_; }
double Box::getMaxWeight() const { return maxWeight_; }
std::vector<std::string> Box::getContents() const { return bookTitles_; }
