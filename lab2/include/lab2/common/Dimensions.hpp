/**
 * @file Dimensions.hpp
 * @brief Класс Dimensions — габариты предмета.
 */
#pragma once
#include <string>

/**
 * @brief Габариты книги или другого предмета в сантиметрах.
 */
class Dimensions
{
private:
    double length_; /**< Длина, см. */
    double width_; /**< Ширина, см. */
    double height_; /**< Высота, см. */

public:
    /**
     * @brief Создаёт габариты.
     * @param length Длина, см.
     * @param width Ширина, см.
     * @param height Высота, см.
     * @throws InvalidDimensionsException Если любой размер не положителен.
     */
    Dimensions(double length, double width, double height);
    /**
     * @brief Вычисляет объём.
     * @return Объём в куб. см.
     */
    double getVolume() const;
    /**
     * @brief Проверяет, помещается ли предмет в заданный объём.
     * @param maxVolume Доступный объём, куб. см.
     * @return true, если объём не превышает maxVolume.
     */
    bool canFitIn(double maxVolume) const;
    /**
     * @brief Форматирует габариты.
     * @return Строка вида «ДxШxВ».
     */
    std::string toString() const;
};
