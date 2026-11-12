#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Rack.hpp"
#include "lab2/warehouse/WarehouseZone.hpp"

class Section
{
private:
    std::string name_;
    WarehouseZone zone_;
    std::vector<Rack> racks_;

public:
    Section(std::string name, WarehouseZone zone);
    void addRack(Rack rack);
    int getRackCount() const;
};
