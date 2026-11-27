#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Section.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/ContactInfo.hpp"

class Warehouse
{
private:
    std::string name_;
    Address address_;
    ContactInfo contact_;
    std::vector<Section> sections_;
    int nextBoxId_ = 1;

public:
    Warehouse(std::string name, Address address, ContactInfo contact);
    void addSection(Section section);
    void printFullStructure() const; // Метод для глубокого вывода

    // Физическое хранение книг: кладёт книгу в первую секцию, где есть место
    bool storeBook(double weight, const std::string &title);
    bool removeBook(const std::string &title);
    int countBook(const std::string &title) const;
    int getTotalStored() const;
};
