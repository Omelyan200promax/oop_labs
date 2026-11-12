#include "lab2/warehouse/Box.hpp"

Box::Box(int id, double maxWeight) : id_(id), maxWeight_(maxWeight), currentWeight_(0) {}

bool Box::putBook(double weight)
{
    if (currentWeight_ + weight <= maxWeight_)
    {
        currentWeight_ += weight;
        return true;
    }
    return false;
}
