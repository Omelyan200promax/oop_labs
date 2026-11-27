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
    int storedCount_ = 0;

public:
    Section(std::string name, WarehouseZone zone);
    void addRack(Rack rack);
    std::string getName() const;
    std::vector<Rack> getRacks() const;
    WarehouseZone getZone() const;
    int getStoredCount() const;

    // Вместимость зоны (capacity) ограничивает число книг в секции
    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    bool removeBook(const std::string &title);
    int countBook(const std::string &title) const;
};
