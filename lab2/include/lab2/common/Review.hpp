/**
 * @file Review.hpp
 * @brief Класс Review — отзыв о книге.
 */
#pragma once
#include <string>
/**
 * @brief Отзыв клиента о книге.
 */
class Review
{
private:
    std::string text_; /**< Текст отзыва. */
    std::string authorName_; /**< Имя автора отзыва. */

public:
    /**
     * @brief Создаёт отзыв.
     * @param text Текст.
     * @param authorName Имя автора отзыва.
     */
    Review(std::string text, std::string authorName);
    /**
     * @brief Возвращает текст отзыва.
     * @return Текст.
     */
    std::string getText() const;
    /**
     * @brief Возвращает имя автора отзыва.
     * @return Имя.
     */
    std::string getAuthor() const;
};
