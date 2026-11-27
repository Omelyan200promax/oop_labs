#pragma once
#include <vector>
#include "lab2/warehouse/Box.hpp"

class Pallet
{
private:
    int id_;
    std::vector<Box> boxes_;

public:
    Pallet(int id);
    void addBox(Box box);
    int getBoxCount() const;
};