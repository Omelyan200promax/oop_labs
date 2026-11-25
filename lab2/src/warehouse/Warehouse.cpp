#include "lab2/warehouse/Warehouse.hpp"

Warehouse::Warehouse(std::string name, Address address, ContactInfo contact)
    : name_(name), address_(address), contact_(contact) {}

void Warehouse::addSection(Section section) { sections_.push_back(section); }
void Warehouse::addEquipment(Equipment eq) { equipment_.push_back(eq); }
void Warehouse::performCheck(InventoryCheck &check) { check.complete(); }

Address Warehouse::getAddress() const { return address_; }
int Warehouse::getTotalSections() const { return sections_.size(); }