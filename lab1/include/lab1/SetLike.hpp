#pragma once

#include "lab1/SetElement.hpp"
#include <memory>
#include <vector>

// Общий интерфейс для Set и MultiSet.
// Через него меню работает с любым множеством, не зная его конкретный тип.
class SetLike
{
public:
    virtual ~SetLike() = default;

    // Базовые операции
    virtual void add(std::shared_ptr<SetElement> element) = 0;
    virtual void remove(std::shared_ptr<SetElement> element) = 0;
    virtual bool contains(std::shared_ptr<SetElement> element) const = 0;
    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;

    // Операции над множествами
    virtual std::shared_ptr<SetLike> unite(const SetLike &other) const = 0;
    virtual std::shared_ptr<SetLike> intersect(const SetLike &other) const = 0;
    virtual std::shared_ptr<SetLike> difference(const SetLike &other) const = 0;
    virtual std::vector<std::shared_ptr<SetLike>> powerSet() const = 0;

    virtual std::shared_ptr<SetElement> elementAt(std::size_t index) const = 0;

    // Вывод
    virtual void print(std::ostream &os) const = 0;
};