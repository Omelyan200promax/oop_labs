/**
 * @file Author.hpp
 * @brief Класс Author — автор книги.
 */
#pragma once
#include <string>

/**
 * @brief Автор книги.
 * @details Хранит имя, фамилию, страну и годы жизни.
 */
class Author
{
private:
    std::string firstName_; /**< Имя. */
    std::string lastName_; /**< Фамилия. */
    std::string country_; /**< Страна. */
    int birthYear_; /**< Год рождения. */
    /**
     * @brief Год смерти; 0, если автор жив.
     */
    int deathYear_; // 0, если жив
public:
    /**
     * @brief Создаёт автора.
     * @param firstName Имя.
     * @param lastName Фамилия.
     * @param country Страна.
     * @param birthYear Год рождения (по умолчанию 1800).
     * @param deathYear Год смерти, 0 — жив (по умолчанию 0).
     */
    Author(std::string firstName, std::string lastName, std::string country, int birthYear = 1800, int deathYear = 0);
    /**
     * @brief Возвращает имя и фамилию.
     * @return Строка «Имя Фамилия».
     */
    std::string getFullName() const;
    /**
     * @brief Возвращает год рождения.
     * @return Год рождения.
     */
    int getBirthYear() const;
    /**
     * @brief Возвращает год смерти.
     * @return Год смерти или 0, если жив.
     */
    int getDeathYear() const;
};
