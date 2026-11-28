/**
 * @file Supplier.hpp
 * @brief Класс Supplier — поставщик.
 */
#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"
#include "lab2/core/Book.hpp"

/**
 * @brief Поставщик книг.
 */
class Supplier
{
private:
    std::string companyName_; /**< Название компании. */
    ContactInfo contact_; /**< Контакты. */

public:
    /**
     * @brief Создаёт поставщика.
     * @param companyName Название компании.
     * @param contact Контакты.
     */
    Supplier(std::string companyName, ContactInfo contact);
    /**
     * @brief Привозит книги: увеличивает остаток в учёте.
     * @details При положительном количестве вызывает Book::addStock и печатает сообщение; иначе ничего не делает.
     * @param book Книга.
     * @param count Количество экземпляров.
     */
    void supplyBooks(Book &book, int count);
};
