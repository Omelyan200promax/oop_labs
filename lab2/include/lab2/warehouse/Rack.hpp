/**
 * @file Rack.hpp
 * @brief Класс Rack — стеллаж.
 */
#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Shelf.hpp"

/**
 * @brief Стеллаж, состоящий из полок.
 */
class Rack
{
private:
    int id_; /**< Номер стеллажа. */
    std::vector<Shelf> shelves_; /**< Полки стеллажа. */

public:
    /**
     * @brief Создаёт пустой стеллаж.
     * @param id Номер стеллажа.
     */
    Rack(int id);
    /**
     * @brief Добавляет полку.
     * @param shelf Полка.
     */
    void addShelf(Shelf shelf);
    /**
     * @brief Количество полок.
     * @return Число полок.
     */
    int getShelfCount() const;
    /**
     * @brief Номер стеллажа.
     * @return Идентификатор.
     */
    int getId() const;
    /**
     * @brief Полки стеллажа.
     * @return Копия списка полок.
     */
    std::vector<Shelf> getShelves() const;

    /**
     * @brief Размещает книгу на первой подходящей полке.
     * @param weight Вес книги, кг.
     * @param title Название.
     * @param nextBoxId Счётчик номеров коробок (растёт при создании новой коробки).
     * @return true, если книга размещена.
     */
    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    /**
     * @brief Снимает одну книгу с полок.
     * @param title Название.
     * @return true, если книга найдена.
     */
    bool removeBook(const std::string &title);
    /**
     * @brief Считает экземпляры книги на стеллаже.
     * @param title Название.
     * @return Количество.
     */
    int countBook(const std::string &title) const;
};
