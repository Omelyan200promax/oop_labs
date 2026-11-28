/**
 * @file Pallet.hpp
 * @brief Класс Pallet — паллета с коробками.
 */
#pragma once
#include <vector>
#include "lab2/warehouse/Box.hpp"

/**
 * @brief Паллета, на которой стоят коробки.
 */
class Pallet
{
private:
    int id_; /**< Номер паллеты. */
    std::vector<Box> boxes_; /**< Коробки на паллете. */

public:
    /**
     * @brief Создаёт пустую паллету.
     * @param id Номер паллеты.
     */
    Pallet(int id);
    /**
     * @brief Ставит коробку на паллету.
     * @param box Коробка.
     */
    void addBox(Box box);
    /**
     * @brief Количество коробок.
     * @return Число коробок на паллете.
     */
    int getBoxCount() const;
};