/**
 * @file Report.hpp
 * @brief Класс Report — отчёт.
 */
#pragma once
#include <string>
/**
 * @brief Текстовый отчёт с заголовком и содержимым.
 */
class Report
{
private:
    std::string title_; /**< Заголовок. */
    std::string content_; /**< Текст отчёта. */

public:
    /**
     * @brief Создаёт отчёт с пустым содержимым.
     * @param title Заголовок.
     */
    Report(std::string title);
    /**
     * @brief Задаёт текст отчёта.
     * @param content Содержимое.
     */
    void setContent(std::string content);
    /**
     * @brief Возвращает заголовок.
     * @return Заголовок.
     */
    std::string getTitle() const;
    /**
     * @brief Возвращает текст отчёта.
     * @return Содержимое.
     */
    std::string getContent() const;
};
