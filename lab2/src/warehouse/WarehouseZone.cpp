#include "lab2/warehouse/WarehouseZone.hpp"

WarehouseZone::WarehouseZone(std::string name, int capacity) : name_(name), capacity_(capacity) {}
std::string WarehouseZone::getName() const { return name_; }
int WarehouseZone::getCapacity() const { return capacity_; }
