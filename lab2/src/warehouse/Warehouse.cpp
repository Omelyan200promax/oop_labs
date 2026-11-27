#include "lab2/warehouse/Warehouse.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/ContactInfo.hpp"
#include <iostream>
#include <map>

Warehouse::Warehouse(std::string name, Address address, ContactInfo contact)
    : name_(name), address_(address), contact_(contact) {}

void Warehouse::addSection(Section section) { sections_.push_back(section); }

void Warehouse::printFullStructure() const
{
    std::cout << "Склад: " << name_ << " (" << address_.getFullAddress() << ")\n";
    for (const auto &sec : sections_)
    {
        std::cout << "  Секция: " << sec.getName()
                  << " [зона \"" << sec.getZone().getName() << "\", занято "
                  << sec.getStoredCount() << "/" << sec.getZone().getCapacity() << "]\n";
        for (const auto &rack : sec.getRacks())
        {
            std::cout << "    Стеллаж №" << rack.getId() << "\n";
            for (const auto &shelf : rack.getShelves())
            {
                std::cout << "      Полка №" << shelf.getId() << ": "
                          << shelf.getBoxCount() << "/" << shelf.getMaxBoxes() << " коробок\n";
                for (const auto &box : shelf.getBoxes())
                {
                    // Сворачиваем одинаковые названия: «Книга x3»
                    std::map<std::string, int> counts;
                    for (const auto &title : box.getContents())
                        ++counts[title];
                    std::cout << "        Коробка №" << box.getId() << " ("
                              << box.getCurrentWeight() << "/" << box.getMaxWeight() << " кг): ";
                    if (counts.empty())
                        std::cout << "пусто";
                    bool first = true;
                    for (const auto &entry : counts)
                    {
                        std::cout << (first ? "" : ", ") << entry.first << " x" << entry.second;
                        first = false;
                    }
                    std::cout << "\n";
                }
            }
        }
    }
}

bool Warehouse::storeBook(double weight, const std::string &title)
{
    for (auto &sec : sections_)
        if (sec.storeBook(weight, title, nextBoxId_))
            return true;
    return false;
}

bool Warehouse::removeBook(const std::string &title)
{
    for (auto &sec : sections_)
        if (sec.removeBook(title))
            return true;
    return false;
}

int Warehouse::countBook(const std::string &title) const
{
    int n = 0;
    for (const auto &sec : sections_)
        n += sec.countBook(title);
    return n;
}

int Warehouse::getTotalStored() const
{
    int n = 0;
    for (const auto &sec : sections_)
        n += sec.getStoredCount();
    return n;
}
