#pragma once
#include <vector>
#include "lab2/warehouse/Box.hpp"

class Shelf
{
private:
    int id_;
    int maxBoxes_;
    int currentBoxes_;

public:
    Shelf(int id, int maxBoxes);
    void addBox();
    bool isFull() const;
    int getFreeSpace() const;
};
