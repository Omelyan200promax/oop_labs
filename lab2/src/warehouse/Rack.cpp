#include "lab2/warehouse/Rack.hpp"

Rack::Rack(int id) : id_(id) {}
void Rack::addShelf(Shelf shelf) { shelves_.push_back(shelf); }
int Rack::getShelfCount() const { return static_cast<int>(shelves_.size()); }
int Rack::getId() const { return id_; }
std::vector<Shelf> Rack::getShelves() const { return shelves_; }

bool Rack::storeBook(double weight, const std::string &title, int &nextBoxId)
{
    for (auto &shelf : shelves_)
        if (shelf.storeBook(weight, title, nextBoxId))
            return true;
    return false;
}

bool Rack::removeBook(const std::string &title)
{
    for (auto &shelf : shelves_)
        if (shelf.removeBook(title))
            return true;
    return false;
}

int Rack::countBook(const std::string &title) const
{
    int n = 0;
    for (const auto &shelf : shelves_)
        n += shelf.countBook(title);
    return n;
}
