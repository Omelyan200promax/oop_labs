#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Section.hpp"
#include "lab2/warehouse/Equipment.hpp"
#include "lab2/warehouse/InventoryCheck.hpp"

class Warehouse
{
private:
    std::string name_;
    std::vector<Section> sections_;
    std::vector<Equipment> equipment_;

public:
    Warehouse(std::string name);
    void addSection(Section section);
    void addEquipment(Equipment eq);
    void performCheck(InventoryCheck &check);
    int getTotalSections() const;
};