/**
 * @file Warehouse.hpp
 * @brief Класс Warehouse — склад.
 */
#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Section.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/ContactInfo.hpp"

/**
 * @brief Склад книг: адрес, контакты и секции.
 * @details Через него выполняется физическое размещение, снятие и подсчёт книг.
 */
class Warehouse
{
private:
    std::string name_; /**< Название склада. */
    Address address_; /**< Адрес. */
    ContactInfo contact_; /**< Контакты. */
    std::vector<Section> sections_; /**< Секции склада. */
    int nextBoxId_ = 1; /**< Следующий свободный номер коробки. */

public:
    /**
     * @brief Создаёт склад без секций.
     * @param name Название.
     * @param address Адрес.
     * @param contact Контакты.
     */
    Warehouse(std::string name, Address address, ContactInfo contact);
    /**
     * @brief Добавляет секцию.
     * @param section Секция.
     */
    void addSection(Section section);
    /**
     * @brief Печатает полную структуру склада.
     * @details Секции, стеллажи, полки и коробки с содержимым — в стандартный вывод.
     */
    void printFullStructure() const; // Метод для глубокого вывода

    /**
     * @brief Размещает книгу в первой секции, где есть место.
     * @param weight Вес книги, кг.
     * @param title Название.
     * @return true, если книга размещена; false, если места нет нигде.
     */
    // Физическое хранение книг: кладёт книгу в первую секцию, где есть место
    bool storeBook(double weight, const std::string &title);
    /**
     * @brief Снимает одну книгу со склада.
     * @param title Название.
     * @return true, если книга найдена и снята.
     */
    bool removeBook(const std::string &title);
    /**
     * @brief Считает экземпляры книги на складе.
     * @param title Название.
     * @return Количество на полках.
     */
    int countBook(const std::string &title) const;
    /**
     * @brief Общее число хранимых книг.
     * @return Сумма по всем секциям.
     */
    int getTotalStored() const;
};
