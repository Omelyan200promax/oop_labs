/**
 * @file Section.hpp
 * @brief Класс Section — секция склада.
 */
#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Rack.hpp"
#include "lab2/warehouse/WarehouseZone.hpp"

/**
 * @brief Секция склада: привязана к зоне и содержит стеллажи.
 * @details Вместимость зоны ограничивает общее число книг в секции.
 */
class Section
{
private:
    std::string name_; /**< Название секции. */
    WarehouseZone zone_; /**< Зона хранения. */
    std::vector<Rack> racks_; /**< Стеллажи секции. */
    int storedCount_ = 0; /**< Сколько книг сейчас хранится. */

public:
    /**
     * @brief Создаёт секцию без стеллажей.
     * @param name Название.
     * @param zone Зона хранения.
     */
    Section(std::string name, WarehouseZone zone);
    /**
     * @brief Добавляет стеллаж.
     * @param rack Стеллаж.
     */
    void addRack(Rack rack);
    /**
     * @brief Название секции.
     * @return Название.
     */
    std::string getName() const;
    /**
     * @brief Стеллажи секции.
     * @return Копия списка стеллажей.
     */
    std::vector<Rack> getRacks() const;
    /**
     * @brief Зона секции.
     * @return Зона хранения.
     */
    WarehouseZone getZone() const;
    /**
     * @brief Количество хранимых книг.
     * @return Число книг в секции.
     */
    int getStoredCount() const;

    /**
     * @brief Размещает книгу в секции.
     * @details Вместимость зоны (capacity) ограничивает число книг в секции.
     * @param weight Вес книги, кг.
     * @param title Название.
     * @param nextBoxId Счётчик номеров коробок.
     * @return true, если книга размещена; false, если секция заполнена или нет места.
     */
    // Вместимость зоны (capacity) ограничивает число книг в секции
    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    /**
     * @brief Снимает одну книгу из секции.
     * @param title Название.
     * @return true, если книга найдена.
     */
    bool removeBook(const std::string &title);
    /**
     * @brief Считает экземпляры книги в секции.
     * @param title Название.
     * @return Количество.
     */
    int countBook(const std::string &title) const;
};
