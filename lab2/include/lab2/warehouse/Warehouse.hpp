#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Section.hpp"
#include "lab2/warehouse/Equipment.hpp"
#include "lab2/warehouse/InventoryCheck.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/ContactInfo.hpp"

class Warehouse
{
private:
    std::string name_;
    Address address_;
    ContactInfo contact_;
    std::vector<Section> sections_;
    std::vector<Equipment> equipment_;

public:
    // Изменили конструктор
    Warehouse(std::string name, Address address, ContactInfo contact);
    void addSection(Section section);
    void addEquipment(Equipment eq);
    void performCheck(InventoryCheck &check);
    int getTotalSections() const;
};