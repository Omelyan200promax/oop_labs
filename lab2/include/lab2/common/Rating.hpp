/**
 * @file Rating.hpp
 * @brief Класс Rating — рейтинг книги.
 */
#pragma once

/**
 * @brief Средний рейтинг по пятибалльной шкале.
 */
class Rating
{
private:
    double totalScore_; /**< Сумма оценок. */
    int count_; /**< Количество оценок. */

public:
    /**
     * @brief Создаёт пустой рейтинг (оценок нет).
     */
    Rating();
    /**
     * @brief Добавляет оценку.
     * @details Оценки вне диапазона 1–5 игнорируются.
     * @param score Оценка от 1 до 5.
     */
    void addScore(int score);
    /**
     * @brief Возвращает средний балл.
     * @return Среднее арифметическое оценок или 0, если оценок нет.
     */
    double getScore() const;
};
