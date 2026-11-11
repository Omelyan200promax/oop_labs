#include "lab2/warehouse/Rack.hpp"

Rack::Rack(int id) : id_(id) {}

void Rack::addShelf(Shelf shelf)
{
    shelves_.push_back(shelf);
}

int Rack::getTotalShelves() const
{
    return shelves_.size();
}
