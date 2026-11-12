#include "lab2/warehouse/Section.hpp"

Section::Section(std::string name, WarehouseZone zone) : name_(name), zone_(zone) {}
void Section::addRack(Rack rack) { racks_.push_back(rack); }
int Section::getRackCount() const { return racks_.size(); }
