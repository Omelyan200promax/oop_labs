#pragma once

#include "lab1/SetElement.hpp"
#include "lab1/SetLike.hpp"
#include <memory>
#include <vector>
#include <string>
#include <ostream>

/**
 * @brief Класс неориентированного канторовского множества.
 * Элементы не повторяются и не упорядочены. Элементом множества
 * может быть как атом, так и другое множество.
 */
class Set : public SetElement, public SetLike
{
public:
    /** @brief Конструктор пустого множества */
    Set() = default;

    // Базовые операции

    /**
     * @brief Добавить элемент в множество
     * @param element Умный указатель на элемент
     * @throws std::invalid_argument Если передан MultiSet
     */
    void add(std::shared_ptr<SetElement> element) override;

    /**
     * @brief Удалить элемент из множества
     * @param element Умный указатель на удаляемый элемент
     */
    void remove(std::shared_ptr<SetElement> element) override;

    /**
     * @brief Проверить наличие элемента
     * @param element Искомый элемент
     * @return true, если элемент есть в множестве
     */
    bool contains(std::shared_ptr<SetElement> element) const override;

    /**
     * @brief Получить мощность множества
     * @return Количество элементов
     */
    std::size_t size() const override;

    /**
     * @brief Проверить, пустое ли множество
     * @return true, если элементов нет
     */
    bool empty() const override;

    // Операции над множествами

    /**
     * @brief Объединить с другим множеством
     * @param other Другое множество
     * @return Новое множество, содержащее элементы обоих
     * @throws std::invalid_argument Если other не является Set
     */
    std::shared_ptr<SetLike> unite(const SetLike &other) const override;

    /**
     * @brief Найти пересечение с другим множеством
     * @param other Другое множество
     * @return Новое множество (пересечение)
     * @throws std::invalid_argument Если other не является Set
     */
    std::shared_ptr<SetLike> intersect(const SetLike &other) const override;

    /**
     * @brief Найти разность с другим множеством
     * @param other Другое множество
     * @return Новое множество (разность)
     * @throws std::invalid_argument Если other не является Set
     */
    std::shared_ptr<SetLike> difference(const SetLike &other) const override;

    /**
     * @brief Построить булеан (множество всех подмножеств)
     * @return Вектор подмножеств
     */
    std::vector<std::shared_ptr<SetLike>> powerSet() const override;

    // Перегрузки операторов

    /** @brief Объединение с присваиванием (+=) */
    Set &operator+=(const Set &other);

    /** @brief Объединение (+) */
    Set operator+(const Set &other) const;

    /** @brief Пересечение с присваиванием (*=) */
    Set &operator*=(const Set &other);

    /** @brief Пересечение (*) */
    Set operator*(const Set &other) const;

    /** @brief Разность с присваиванием (-=) */
    Set &operator-=(const Set &other);

    /** @brief Разность (-) */
    Set operator-(const Set &other) const;

    /** @brief Сравнение на равенство (==) */
    bool operator==(const Set &other) const;

    /** @brief Сравнение на неравенство (!=) */
    bool operator!=(const Set &other) const;

    /**
     * @brief Проверка принадлежности элемента ([])
     * @param element Искомый элемент
     * @return true, если элемент принадлежит множеству
     */
    bool operator[](std::shared_ptr<SetElement> element) const;

    // Методы SetElement (нужны, потому что Set — тоже элемент)

    /**
     * @brief Сравнить с другим элементом
     * @param other Другой элемент
     * @return true, если элементы равны
     */
    bool equals(const SetElement &other) const override;

    /**
     * @brief Вывести множество в поток
     * @param os Поток вывода
     */
    void print(std::ostream &os) const override;

    /**
     * @brief Создать копию множества
     * @return Умный указатель на копию
     */
    std::shared_ptr<SetElement> clone() const override;

    /**
     * @brief Получить элемент по индексу
     * @param index Индекс элемента
     * @return Умный указатель на элемент
     * @throws std::out_of_range Если индекс вне диапазона
     */
    std::shared_ptr<SetElement> elementAt(std::size_t index) const override;

    /** @brief Проверка, является ли объект обычным множеством (всегда true) */
    bool isPlainSet() const override { return true; }

    /**
     * @brief Создать множество из строки
     * @param text Строка вида "{a, b, {c}}"
     * @return Новое множество
     * @throws std::invalid_argument Если строка некорректна
     */
    static Set fromString(const std::string &text);

private:
    std::vector<std::shared_ptr<SetElement>> elements_; ///< Внутреннее хранилище элементов
};

/**
 * @brief Вывод множества в поток (<<)
 * @param os Поток вывода
 * @param set Множество
 * @return Ссылка на поток
 */
std::ostream &operator<<(std::ostream &os, const Set &set);