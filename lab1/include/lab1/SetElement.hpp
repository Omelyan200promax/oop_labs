#pragma once

#include <iostream>
#include <memory>

// Абстрактный базовый класс для всех элементов множества.
// Наследники: Atom, Set, MultiSet.
class SetElement
{
public:
    virtual ~SetElement() = default;

    // Сравнение с другим элементом на равенство.
    virtual bool equals(const SetElement &other) const = 0;

    // Вывод элемента в поток (например, std::cout).
    virtual void print(std::ostream &os) const = 0;

    // Копирование: возвращает новый объект — копию текущего.
    virtual std::shared_ptr<SetElement> clone() const = 0;

    // Для проверки: исключение добавления мультимн-ва во множество и наоборот
    virtual bool isMultiSet() const { return false; }
    virtual bool isPlainSet() const { return false; }
};