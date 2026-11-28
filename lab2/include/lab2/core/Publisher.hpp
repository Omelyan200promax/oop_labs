/**
 * @file Publisher.hpp
 * @brief Класс Publisher — издательство.
 */
#pragma once
#include <string>

/**
 * @brief Издательство.
 */
class Publisher
{
private:
    std::string name_; /**< Название. */
    std::string city_; /**< Город. */

public:
    /**
     * @brief Создаёт издательство.
     * @param name Название.
     * @param city Город.
     */
    Publisher(std::string name, std::string city);
    /**
     * @brief Краткая информация об издательстве.
     * @return Строка «Название (город)».
     */
    std::string getInfo() const;
};
