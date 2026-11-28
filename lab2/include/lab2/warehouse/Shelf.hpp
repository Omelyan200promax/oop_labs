/**
 * @file Shelf.hpp
 * @brief Класс Shelf — полка.
 */
#pragma once
#include <string>
#include <vector>
#include "lab2/warehouse/Box.hpp"

/**
 * @brief Полка, на которой стоит ограниченное число коробок.
 */
class Shelf
{
private:
    int id_; /**< Номер полки. */
    int maxBoxes_; /**< Максимум коробок. */
    std::vector<Box> boxes_; /**< Коробки на полке. */

public:
    /**
     * @brief Максимальный вес новой коробки, создаваемой при раскладке книг (кг).
     */
    // Максимальный вес новой коробки, создаваемой при раскладке книг
    static constexpr double DEFAULT_BOX_WEIGHT = 20.0;

    /**
     * @brief Создаёт пустую полку.
     * @param id Номер полки.
     * @param maxBoxes Максимум коробок.
     */
    Shelf(int id, int maxBoxes);
    /**
     * @brief Ставит готовую коробку на полку.
     * @param box Коробка.
     * @throws CapacityExceededException Если полка заполнена.
     */
    void addBox(Box box);
    /**
     * @brief Количество коробок.
     * @return Число коробок на полке.
     */
    int getBoxCount() const;
    /**
     * @brief Номер полки.
     * @return Идентификатор.
     */
    int getId() const;
    /**
     * @brief Вместимость полки.
     * @return Максимум коробок.
     */
    int getMaxBoxes() const;
    /**
     * @brief Коробки полки.
     * @return Копия списка коробок.
     */
    std::vector<Box> getBoxes() const;

    /**
     * @brief Кладёт книгу в подходящую коробку или заводит новую.
     * @details Новая коробка создаётся, только если на полке есть место; её вес — DEFAULT_BOX_WEIGHT.
     * @param weight Вес книги, кг.
     * @param title Название.
     * @param nextBoxId Номер для новой коробки; увеличивается только при её создании.
     * @return true, если книга размещена.
     */
    // Кладёт книгу в подходящую коробку (или заводит новую, если есть место на полке).
    // nextBoxId увеличивается только при создании новой коробки.
    bool storeBook(double weight, const std::string &title, int &nextBoxId);
    /**
     * @brief Снимает одну книгу с полки.
     * @param title Название.
     * @return true, если книга найдена.
     */
    bool removeBook(const std::string &title);
    /**
     * @brief Считает экземпляры книги на полке.
     * @param title Название.
     * @return Количество.
     */
    int countBook(const std::string &title) const;
};
