/**
 * @file Equipment.hpp
 * @brief Класс Equipment — оборудование склада.
 */
#pragma once
#include <string>

/**
 * @brief Единица оборудования склада (погрузчик, сканер, фургон).
 */
class Equipment
{
private:
    std::string name_; /**< Название. */
    bool isWorking_; /**< Признак исправности. */

public:
    /**
     * @brief Создаёт оборудование.
     * @param name Название.
     * @param isWorking true — исправно.
     */
    Equipment(std::string name, bool isWorking);
    /**
     * @brief Проверяет исправность.
     * @return true, если оборудование работает.
     */
    bool checkStatus() const;
    /**
     * @brief Название оборудования.
     * @return Название.
     */
    std::string getName() const;
    /**
     * @brief Ремонтирует оборудование (делает исправным).
     */
    void repair();
};
