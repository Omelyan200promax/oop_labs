#pragma once

#include "lab1/SetElement.hpp"
#include "lab1/SetLike.hpp"
#include <memory>
#include <vector>
#include <string>

// Неориентированное мультимножество:
// элементы могут повторяться.
class MultiSet : public SetElement, public SetLike
{
public:
    MultiSet() = default;

    // Базовые операции
    void add(std::shared_ptr<SetElement> element) override;
    void remove(std::shared_ptr<SetElement> element) override;
    bool contains(std::shared_ptr<SetElement> element) const override;
    std::size_t count(std::shared_ptr<SetElement> element) const;
    std::size_t size() const override;
    bool empty() const override;
    std::shared_ptr<SetElement> elementAt(std::size_t index) const override;

    // Операции над множествами
    std::shared_ptr<SetLike> unite(const SetLike &other) const override;
    std::shared_ptr<SetLike> intersect(const SetLike &other) const override;
    std::shared_ptr<SetLike> difference(const SetLike &other) const override;
    std::vector<std::shared_ptr<SetLike>> powerSet() const override;

    // Перегрузки операторов
    MultiSet &operator+=(const MultiSet &other);
    MultiSet operator+(const MultiSet &other) const;

    MultiSet &operator*=(const MultiSet &other);
    MultiSet operator*(const MultiSet &other) const;

    MultiSet &operator-=(const MultiSet &other);
    MultiSet operator-(const MultiSet &other) const;

    bool operator==(const MultiSet &other) const;
    bool operator!=(const MultiSet &other) const;

    std::size_t operator[](std::shared_ptr<SetElement> element) const;

    // Методы SetElement
    bool equals(const SetElement &other) const override;
    void print(std::ostream &os) const override;
    std::shared_ptr<SetElement> clone() const override;

    // Флаги типа
    bool isMultiSet() const override { return true; }

    // Парсинг из строки
    static MultiSet fromString(const std::string &text);

    // Копирование — по умолчанию
    MultiSet(const MultiSet &other) = default;
    MultiSet &operator=(const MultiSet &other) = default;

private:
    // Храним пары: элемент + количество повторов
    std::vector<std::pair<std::shared_ptr<SetElement>, std::size_t>> elements_;

    void buildPowerSet(std::vector<std::shared_ptr<SetLike>> &result,
                       std::size_t index,
                       std::shared_ptr<MultiSet> current) const;
};

std::ostream &operator<<(std::ostream &os, const MultiSet &multiset);