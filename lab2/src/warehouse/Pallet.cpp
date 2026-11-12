#include "lab2/warehouse/Pallet.hpp"

Pallet::Pallet(int id, int maxBoxes) : id_(id), maxBoxes_(maxBoxes), currentBoxes_(0) {}

bool Pallet::addBox()
{
    if (currentBoxes_ < maxBoxes_)
    {
        currentBoxes_++;
        return true;
    }
    return false;
}
int Pallet::getFreeSpace() const { return maxBoxes_ - currentBoxes_; }
