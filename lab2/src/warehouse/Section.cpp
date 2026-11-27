#include "lab2/warehouse/Section.hpp"

Section::Section(std::string name, WarehouseZone zone) : name_(name), zone_(zone) {}
void Section::addRack(Rack rack) { racks_.push_back(rack); }
std::string Section::getName() const { return name_; }
std::vector<Rack> Section::getRacks() const { return racks_; }
WarehouseZone Section::getZone() const { return zone_; }
int Section::getStoredCount() const { return storedCount_; }

bool Section::storeBook(double weight, const std::string &title, int &nextBoxId)
{
    if (storedCount_ >= zone_.getCapacity())
        return false;
    for (auto &rack : racks_)
    {
        if (rack.storeBook(weight, title, nextBoxId))
        {
            ++storedCount_;
            return true;
        }
    }
    return false;
}

bool Section::removeBook(const std::string &title)
{
    for (auto &rack : racks_)
    {
        if (rack.removeBook(title))
        {
            --storedCount_;
            return true;
        }
    }
    return false;
}

int Section::countBook(const std::string &title) const
{
    int n = 0;
    for (const auto &rack : racks_)
        n += rack.countBook(title);
    return n;
}
