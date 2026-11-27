#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Box.hpp"

class Shelf
{
private:
    int id_;
    int maxBoxes_;
    std::vector<Box> boxes_;

public:
    // Максимальный вес новой коробки, создаваемой при раскладке книг
    static constexpr double DEFAULT_BOX_WEIGHT = 20.0;

    Shelf(int id, int maxBoxes);
    void addBox(Box box);
    int getBoxCount() const;
    int getId() const;
    int getMaxBoxes() const;
    std::vector<Box> getBoxes() const;

    // Кладёт книгу в подходящую коробку (или заводит новую, если есть место на полке).
    // nextBoxId увеличивается только при создании новой коробки.
    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    bool removeBook(const std::string &title);
    int countBook(const std::string &title) const;
};
