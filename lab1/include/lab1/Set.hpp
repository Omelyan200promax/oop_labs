#pragma once

#include "lab1/SetElement.hpp"
#include "lab1/SetLike.hpp"
#include <memory>
#include <vector>
#include <string>

// Неориентированное канторовское множество:
// элементы не повторяются и не упорядочены.
class Set : public SetElement, public SetLike
{
public:
    Set() = default;

    // Базовые операции
    void add(std::shared_ptr<SetElement> element) override;
    void remove(std::shared_ptr<SetElement> element) override;
    bool contains(std::shared_ptr<SetElement> element) const override;
    std::size_t size() const override;
    bool empty() const override;

    // Операции над множествами
    std::shared_ptr<SetLike> unite(const SetLike &other) const override;
    std::shared_ptr<SetLike> intersect(const SetLike &other) const override;
    std::shared_ptr<SetLike> difference(const SetLike &other) const override;
    std::vector<std::shared_ptr<SetLike>> powerSet() const override;

    // Перегрузки операторов
    Set &operator+=(const Set &other);
    Set operator+(const Set &other) const;

    Set &operator*=(const Set &other);
    Set operator*(const Set &other) const;

    Set &operator-=(const Set &other);
    Set operator-(const Set &other) const;

    bool operator==(const Set &other) const;
    bool operator!=(const Set &other) const;

    bool operator[](std::shared_ptr<SetElement> element) const;

    // Методы SetElement (нужны, потому что Set — тоже элемент)
    bool equals(const SetElement &other) const override;
    void print(std::ostream &os) const override;
    std::shared_ptr<SetElement> clone() const override;

    // Метод для получения эл-та по индексу
    std::shared_ptr<SetElement> elementAt(std::size_t index) const override;

    // Для проверки, чтобы исключить включение мультимн-ва в мн-во
    bool isPlainSet() const override { return true; }

    // Парсинг из строки: "{a, b, {c}}"
    static Set fromString(const std::string &text);

private:
    std::vector<std::shared_ptr<SetElement>> elements_;
};

// Вывод в поток
std::ostream &operator<<(std::ostream &os, const Set &set);