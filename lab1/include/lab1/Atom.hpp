#pragma once

#include "lab1/SetElement.hpp"
#include <string>

/**
 * @brief Класс, представляющий простой (неделимый) элемент множества — атом.
 * Может хранить строки, числа или буквы.
 */

// Простой элемент множества: буква, число, слово.
class Atom : public SetElement
{
public:
    /**
     * @brief Конструктор атома
     * @param value Строковое значение элемента
     */
    explicit Atom(std::string value);

    /**
     * @brief Получить значение атома
     * @return Константная ссылка на строку
     */
    const std::string &value() const;

    /**
     * @brief Сравнить с другим элементом
     * @param other Другой элемент
     * @return true если элементы равны, иначе false
     */
    bool equals(const SetElement &other) const override;

    /**
     * @brief Вывести элемент в поток
     * @param os Поток вывода (например, std::cout)
     */
    void print(std::ostream &os) const override;

    /**
     * @brief Создать копию элемента
     * @return Умный указатель на копию
     */
    std::shared_ptr<SetElement> clone() const override;

private:
    std::string value_;
};