/**
 * @file Box.hpp
 * @brief Класс Box — коробка с книгами.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @brief Коробка с книгами, ограниченная по суммарному весу.
 * @details Хранит названия книг и вес каждой, чтобы при извлечении корректно уменьшать вес коробки.
 */
class Box
{
private:
    int id_; /**< Номер коробки. */
    double maxWeight_; /**< Максимально допустимый вес, кг. */
    double currentWeight_; /**< Текущий вес содержимого, кг. */
    std::vector<std::string> bookTitles_; /**< Названия книг в коробке. */
    std::vector<double> bookWeights_; /**< Вес каждой книги (параллельно bookTitles_), кг. */

public:
    /**
     * @brief Создаёт пустую коробку.
     * @param id Номер коробки.
     * @param maxWeight Максимальный вес, кг.
     */
    Box(int id, double maxWeight);
    /**
     * @brief Кладёт книгу в коробку.
     * @param weight Вес книги, кг.
     * @param title Название книги.
     * @return true, если книга поместилась по весу; иначе false (коробка не меняется).
     */
    bool putBook(double weight, const std::string &title);
    /**
     * @brief Достаёт одну книгу с указанным названием.
     * @param title Название книги.
     * @return true, если книга найдена и извлечена.
     */
    bool removeBook(const std::string &title);
    /**
     * @brief Считает экземпляры книги в коробке.
     * @param title Название книги.
     * @return Количество экземпляров.
     */
    int countBook(const std::string &title) const;
    /**
     * @brief Номер коробки.
     * @return Идентификатор.
     */
    int getId() const;
    /**
     * @brief Текущий вес.
     * @return Вес содержимого, кг.
     */
    double getCurrentWeight() const;
    /**
     * @brief Предельный вес.
     * @return Максимальный вес, кг.
     */
    double getMaxWeight() const;
    /**
     * @brief Содержимое коробки.
     * @return Названия книг (по одному на экземпляр).
     */
    std::vector<std::string> getContents() const;
};
