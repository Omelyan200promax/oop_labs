/**
 * @file WarehouseZone.hpp
 * @brief Класс WarehouseZone — зона склада.
 */
#pragma once
#include <string>

/**
 * @brief Зона хранения с ограниченной вместимостью.
 */
class WarehouseZone
{
private:
    std::string name_; /**< Название зоны. */
    int capacity_; /**< Вместимость, шт. книг. */

public:
    /**
     * @brief Создаёт зону.
     * @param name Название.
     * @param capacity Вместимость в книгах.
     */
    WarehouseZone(std::string name, int capacity);
    /**
     * @brief Название зоны.
     * @return Название.
     */
    std::string getName() const;
    /**
     * @brief Вместимость зоны.
     * @return Максимум книг.
     */
    int getCapacity() const;
};
