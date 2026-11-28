/**
 * @file Category.hpp
 * @brief Класс Category — категория книги.
 */
#pragma once
#include <string>

/**
 * @brief Категория каталога.
 */
class Category
{
private:
    std::string name_; /**< Название. */
    std::string description_; /**< Описание. */

public:
    /**
     * @brief Создаёт категорию.
     * @param name Название.
     * @param description Описание.
     */
    Category(std::string name, std::string description);
    /**
     * @brief Название категории.
     * @return Название.
     */
    std::string getName() const;
};
