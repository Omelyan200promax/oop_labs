#include "lab2/warehouse/Shelf.hpp"
#include "lab2/exceptions/CapacityExceededException.hpp"

Shelf::Shelf(int id, int maxBoxes) : id_(id), maxBoxes_(maxBoxes) {}

void Shelf::addBox(Box box)
{
    if (boxes_.size() >= static_cast<size_t>(maxBoxes_))
        throw CapacityExceededException("Полка переполнена");
    boxes_.push_back(box);
}

int Shelf::getBoxCount() const { return static_cast<int>(boxes_.size()); }
int Shelf::getId() const { return id_; }
int Shelf::getMaxBoxes() const { return maxBoxes_; }
std::vector<Box> Shelf::getBoxes() const { return boxes_; }

bool Shelf::storeBook(double weight, const std::string &title, int &nextBoxId)
{
    for (auto &box : boxes_)
        if (box.putBook(weight, title))
            return true;

    if (boxes_.size() < static_cast<size_t>(maxBoxes_))
    {
        Box box(nextBoxId, DEFAULT_BOX_WEIGHT);
        if (box.putBook(weight, title))
        {
            ++nextBoxId;
            boxes_.push_back(box);
            return true;
        }
    }
    return false;
}

bool Shelf::removeBook(const std::string &title)
{
    for (auto &box : boxes_)
        if (box.removeBook(title))
            return true;
    return false;
}

int Shelf::countBook(const std::string &title) const
{
    int n = 0;
    for (const auto &box : boxes_)
        n += box.countBook(title);
    return n;
}
