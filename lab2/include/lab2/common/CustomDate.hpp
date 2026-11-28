/**
 * @file CustomDate.hpp
 * @brief Класс CustomDate — простая календарная дата.
 */
#pragma once
#include <string>

/**
 * @brief Календарная дата (день, месяц, год).
 * @details Корректность значений при создании не проверяется.
 */
class CustomDate
{
private:
    int day_; /**< День месяца. */
    int month_; /**< Номер месяца (1–12). */
    int year_; /**< Год. */

public:
    /**
     * @brief Создаёт дату.
     * @param day День месяца.
     * @param month Месяц.
     * @param year Год.
     */
    CustomDate(int day, int month, int year);
    /**
     * @brief Форматирует дату.
     * @return Строка вида ДД.ММ.ГГГГ.
     */
    std::string toString() const;
    /**
     * @brief Проверяет, високосный ли год.
     * @return true, если год високосный.
     */
    bool isLeapYear() const;
    /**
     * @brief Возвращает день.
     * @return День месяца.
     */
    int getDay() const;
    /**
     * @brief Возвращает месяц.
     * @return Номер месяца.
     */
    int getMonth() const;
    /**
     * @brief Возвращает год.
     * @return Год.
     */
    int getYear() const;
    /**
     * @brief Сравнивает даты хронологически.
     * @param other Дата для сравнения.
     * @return true, если эта дата раньше или равна other.
     */
    bool operator<=(const CustomDate &other) const;
};
