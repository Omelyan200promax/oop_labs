#pragma once
#include <string>
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
    int getShelfCount() const;
    int getId() const;
    std::vector<Shelf> getShelves() const;

    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    bool removeBook(const std::string &title);
    int countBook(const std::string &title) const;
};
