#pragma once
#include <vector>
#include "lab2/warehouse/Shelf.hpp"

class Rack
{
private:
    int id_;
    std::vector<Shelf> shelves_;

public:
    Rack(int id);
    void addShelf(Shelf shelf);
    int getTotalShelves() const;
};
