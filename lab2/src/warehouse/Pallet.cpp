#include "lab2/warehouse/Pallet.hpp"

Pallet::Pallet(int id) : id_(id) {}
void Pallet::addBox(Box box) { boxes_.push_back(box); }
int Pallet::getBoxCount() const { return boxes_.size(); }
