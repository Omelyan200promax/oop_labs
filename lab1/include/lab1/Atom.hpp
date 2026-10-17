#pragma once

#include "lab1/SetElement.hpp"
#include <string>

// Простой элемент множества: буква, число, слово.
class Atom : public SetElement
{
public:
    explicit Atom(std::string value);

    const std::string &value() const;

    bool equals(const SetElement &other) const override;
    void print(std::ostream &os) const override;
    std::shared_ptr<SetElement> clone() const override;

private:
    std::string value_;
};