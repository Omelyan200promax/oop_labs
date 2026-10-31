#pragma once

#include "lab1/SetElement.hpp"
#include "lab1/SetLike.hpp"
#include <memory>
#include <vector>
#include <string>
#include <ostream>

/**
 * @brief Неориентированное мультимножество.
 *
 * В отличие от обычного множества, элементы могут повторяться.
 */
class MultiSet : public SetElement, public SetLike
{
public:
    /** @brief Конструктор по умолчанию (создает пустое мультимножество) */
    MultiSet() = default;

    // Базовые операции

    /**
     * @brief Добавить элемент (увеличивает счетчик повторов)
     * @param element Умный указатель на элемент
     * @throws std::invalid_argument Если передан объект Set (смешивание запрещено)
     */
    void add(std::shared_ptr<SetElement> element) override;

    /**
     * @brief Удалить один экземпляр элемента (уменьшает счетчик)
     * @param element Умный указатель на элемент
     */
    void remove(std::shared_ptr<SetElement> element) override;

    /**
     * @brief Проверить наличие элемента
     * @param element Искомый элемент
     * @return true, если элемент есть (хотя бы один раз)
     */
    bool contains(std::shared_ptr<SetElement> element) const override;

    /**
     * @brief Получить количество повторов элемента
     * @param element Искомый элемент
     * @return Сколько раз элемент встречается
     */
    std::size_t count(std::shared_ptr<SetElement> element) const;

    /**
     * @brief Получить общее количество элементов (с учетом повторов)
     * @return Мощность мультимножества
     */
    std::size_t size() const override;

    /**
     * @brief Проверить, пустое ли мультимножество
     * @return true, если элементов нет
     */
    bool empty() const override;

    /**
     * @brief Получить элемент по индексу в развернутом виде
     * @param index Индекс элемента
     * @return Умный указатель на элемент
     * @throws std::out_of_range Если индекс вне диапазона
     */
    std::shared_ptr<SetElement> elementAt(std::size_t index) const override;

    // Операции над множествами

    /**
     * @brief Объединить с другим мультимножеством (берется максимум повторов)
     * @param other Другое мультимножество
     * @return Новое мультимножество
     * @throws std::invalid_argument Если other не является MultiSet
     */
    std::shared_ptr<SetLike> unite(const SetLike &other) const override;

    /**
     * @brief Найти пересечение (берется минимум повторов)
     * @param other Другое мультимножество
     * @return Новое мультимножество
     * @throws std::invalid_argument Если other не является MultiSet
     */
    std::shared_ptr<SetLike> intersect(const SetLike &other) const override;

    /**
     * @brief Найти разность (повторы вычитаются)
     * @param other Другое мультимножество
     * @return Новое мультимножество
     * @throws std::invalid_argument Если other не является MultiSet
     */
    std::shared_ptr<SetLike> difference(const SetLike &other) const override;

    /**
     * @brief Построить булеан (множество всех подмножеств)
     * @return Вектор подмножеств
     */
    std::vector<std::shared_ptr<SetLike>> powerSet() const override;

    // Перегрузки операторов

    /** @brief Объединение с присваиванием (+=) */
    MultiSet &operator+=(const MultiSet &other);

    /** @brief Объединение (+) */
    MultiSet operator+(const MultiSet &other) const;

    /** @brief Пересечение с присваиванием (*=) */
    MultiSet &operator*=(const MultiSet &other);

    /** @brief Пересечение (*) */
    MultiSet operator*(const MultiSet &other) const;

    /** @brief Разность с присваиванием (-=) */
    MultiSet &operator-=(const MultiSet &other);

    /** @brief Разность (-) */
    MultiSet operator-(const MultiSet &other) const;

    /** @brief Сравнение на равенство (==) */
    bool operator==(const MultiSet &other) const;

    /** @brief Сравнение на неравенство (!=) */
    bool operator!=(const MultiSet &other) const;

    /**
     * @brief Получить количество повторов ([])
     * @param element Искомый элемент
     * @return Количество повторов
     */
    std::size_t operator[](std::shared_ptr<SetElement> element) const;

    // Методы SetElement

    /**
     * @brief Сравнить с другим элементом
     * @param other Другой элемент
     * @return true, если элементы равны
     */
    bool equals(const SetElement &other) const override;

    /**
     * @brief Вывести мультимножество в поток
     * @param os Поток вывода
     */
    void print(std::ostream &os) const override;

    /**
     * @brief Создать копию мультимножества
     * @return Умный указатель на копию
     */
    std::shared_ptr<SetElement> clone() const override;

    /** @brief Проверка, является ли объект мультимножеством (всегда true) */
    bool isMultiSet() const override { return true; }

    /**
     * @brief Создать мультимножество из строки
     * @param text Строка вида "{a, a, b}"
     * @return Новое мультимножество
     * @throws std::invalid_argument Если строка некорректна
     */
    static MultiSet fromString(const std::string &text);

    /** @brief Конструктор копирования */
    MultiSet(const MultiSet &other) = default;

    /** @brief Оператор присваивания копированием */
    MultiSet &operator=(const MultiSet &other) = default;

private:
    /// Внутреннее хранилище: пары (элемент, количество повторов)
    std::vector<std::pair<std::shared_ptr<SetElement>, std::size_t>> elements_;

    /**
     * @brief Рекурсивная функция для построения булеана
     * @param result Вектор для сохранения подмножеств
     * @param index Индекс текущего элемента
     * @param current Текущее подмножество
     */
    void buildPowerSet(std::vector<std::shared_ptr<SetLike>> &result,
                       std::size_t index,
                       std::shared_ptr<MultiSet> current) const;
};

/**
 * @brief Вывод мультимножества в поток (<<)
 * @param os Поток вывода
 * @param multiset Мультимножество
 * @return Ссылка на поток
 */
std::ostream &operator<<(std::ostream &os, const MultiSet &multiset);