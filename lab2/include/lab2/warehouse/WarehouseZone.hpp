#pragma once
#include <string>

class WarehouseZone
{
private:
    std::string name_;
    int capacity_;

public:
    WarehouseZone(std::string name, int capacity);
    std::string getName() const;
    int getCapacity() const;
};
