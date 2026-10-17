#include "lab1/Atom.hpp"

Atom::Atom(std::string value)
    : value_(std::move(value)) {}

const std::string &Atom::value() const
{
    return value_;
}

bool Atom::equals(const SetElement &other) const
{
    const Atom *atom = dynamic_cast<const Atom *>(&other);
    if (atom == nullptr)
    {
        return false;
    }
    return value_ == atom->value_;
}

void Atom::print(std::ostream &os) const
{
    os << value_;
}

std::shared_ptr<SetElement> Atom::clone() const
{
    return std::make_shared<Atom>(value_);
}