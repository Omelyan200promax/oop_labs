#include "lab2/warehouse/Shelf.hpp"
#include "lab2/exceptions/CapacityExceededException.hpp"

Shelf::Shelf(int id, int maxBoxes) : id_(id), maxBoxes_(maxBoxes), currentBoxes_(0) {}

void Shelf::addBox()
{
    if (isFull())
    {
        throw CapacityExceededException("Полка заполнена");
    }
    currentBoxes_++;
}

bool Shelf::isFull() const
{
    return currentBoxes_ >= maxBoxes_;
}

int Shelf::getFreeSpace() const
{
    return maxBoxes_ - currentBoxes_;
}
