#include "lab2/warehouse/InventoryCheck.hpp"

InventoryCheck::InventoryCheck(CustomDate date) : date_(date), isCompleted_(false) {}
void InventoryCheck::complete() { isCompleted_ = true; }
bool InventoryCheck::isCompleted() const { return isCompleted_; }
