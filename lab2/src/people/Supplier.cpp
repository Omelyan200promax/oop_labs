#include "lab2/people/Supplier.hpp"
#include <iostream>

Supplier::Supplier(std::string companyName, ContactInfo contact) : companyName_(companyName), contact_(contact) {}
void Supplier::supplyBooks(Book &book, int count)
{
    if (count > 0)
    {
        book.addStock(count);
        std::cout << "Поставщик " << companyName_ << " привез " << count << " шт. книги \"" << book.getTitle() << "\"\n";
    }
}