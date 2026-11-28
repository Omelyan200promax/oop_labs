/**
 * @file Genre.hpp
 * @brief Класс Genre — жанр книги.
 */
#pragma once
#include <string>

/**
 * @brief Литературный жанр.
 */
class Genre
{
private:
    std::string name_; /**< Название. */
    std::string description_; /**< Описание. */

public:
    /**
     * @brief Создаёт жанр.
     * @param name Название.
     * @param description Описание.
     */
    Genre(std::string name, std::string description);

    /**
     * @brief Описание жанра.
     * @return Строка «Название: описание».
     */
    std::string getDescription() const;
    /**
     * @brief Название жанра.
     * @return Название.
     */
    std::string getName() const;
};
