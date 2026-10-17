#include "lab1/Set.hpp"
#include "lab1/Atom.hpp"
#include <sstream>
#include <stdexcept>

// Базовые операции

void Set::add(std::shared_ptr<SetElement> element)
{
    if (element->isMultiSet())
    {
        throw std::invalid_argument("В Set нельзя добавить MultiSet");
    }
    if (!contains(element))
    {
        elements_.push_back(element);
    }
}

// Удаление элемента
void Set::remove(std::shared_ptr<SetElement> element)
{
    for (auto it = elements_.begin(); it != elements_.end(); ++it)
    {
        if ((*it)->equals(*element))
        {
            elements_.erase(it);
            return;
        }
    }
}

// Проверка на содержание элемента в множестве
bool Set::contains(std::shared_ptr<SetElement> element) const
{
    for (const auto &current : elements_)
    {
        if (current->equals(*element))
        {
            return true;
        }
    }
    return false;
}

// Размер множества
std::size_t Set::size() const
{
    return elements_.size();
}

bool Set::empty() const
{
    return elements_.empty();
}

// Объединение 2 множеств
std::shared_ptr<SetLike> Set::unite(const SetLike &other) const
{
    auto result = std::make_shared<Set>(*this);

    for (std::size_t i = 0; i < other.size(); ++i)
    {
        auto element = other.elementAt(i);
        result->add(element);
    }

    return result;
}

// Пересечение 2 множеств
std::shared_ptr<SetLike> Set::intersect(const SetLike &other) const
{
    auto result = std::make_shared<Set>();

    for (const auto &element : elements_)
    {
        if (other.contains(element))
        {
            result->add(element);
        }
    }

    return result;
}

// Разность 2 множеств
std::shared_ptr<SetLike> Set::difference(const SetLike &other) const
{
    auto result = std::make_shared<Set>();

    for (const auto &element : elements_)
    {
        if (!other.contains(element))
        {
            result->add(element);
        }
    }

    return result;
}

// сравнение множеств
bool Set::equals(const SetElement &other) const
{
    const Set *other_set = dynamic_cast<const Set *>(&other);
    if (other_set == nullptr)
    {
        return false;
    }
    if (size() != other_set->size())
    {
        return false;
    }
    for (const auto &element : elements_)
    {
        if (!other_set->contains(element))
        {
            return false;
        }
    }
    return true;
}
// вывод множества в поток
void Set::print(std::ostream &os) const
{
    os << "{";
    bool first = true;
    for (const auto &element : elements_)
    {
        if (!first)
        {
            os << ", ";
        }
        element->print(os);
        first = false;
    }
    os << "}";
}

// копирование
std::shared_ptr<SetElement> Set::clone() const
{
    return std::make_shared<Set>(*this);
}

// Получение элемента множества по индексу
std::shared_ptr<SetElement> Set::elementAt(std::size_t index) const
{
    return elements_.at(index);
}

// Операторы

// Объединение

Set &Set::operator+=(const Set &other)
{
    for (const auto &element : other.elements_)
    {
        add(element);
    }
    return *this;
}

Set Set::operator+(const Set &other) const
{
    Set result = *this;
    result += other;
    return result;
}

//  Пересечение

Set &Set::operator*=(const Set &other)
{
    for (auto it = elements_.begin(); it != elements_.end();)
    {
        if (!other.contains(*it))
        {
            it = elements_.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return *this;
}

Set Set::operator*(const Set &other) const
{
    Set result = *this;
    result *= other;
    return result;
}

//  Разность

Set &Set::operator-=(const Set &other)
{
    for (auto it = elements_.begin(); it != elements_.end();)
    {
        if (other.contains(*it))
        {
            it = elements_.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return *this;
}

Set Set::operator-(const Set &other) const
{
    Set result = *this;
    result -= other;
    return result;
}

// Сравнение

bool Set::operator==(const Set &other) const
{
    if (size() != other.size())
    {
        return false;
    }
    for (const auto &element : elements_)
    {
        if (!other.contains(element))
        {
            return false;
        }
    }
    return true;
}

bool Set::operator!=(const Set &other) const
{
    return !(*this == other);
}

// Индексация: проверка принадлежности

bool Set::operator[](std::shared_ptr<SetElement> element) const
{
    return contains(element);
}

//  Вывод в поток (снаружи класса)

std::ostream &operator<<(std::ostream &os, const Set &set)
{
    set.print(os);
    return os;
}

// Составление булеана
std::vector<std::shared_ptr<SetLike>> Set::powerSet() const
{
    std::vector<std::shared_ptr<SetLike>> result;
    std::size_t n = size();

    std::size_t total = 1;
    for (std::size_t i = 0; i < n; ++i)
    {
        total *= 2;
    }

    for (std::size_t mask = 0; mask < total; ++mask)
    {
        auto subset = std::make_shared<Set>();
        for (std::size_t i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                subset->add(elementAt(i));
            }
        }
        result.push_back(subset);
    }

    return result;
}

// Парсинг строки с множеством
Set Set::fromString(const std::string &text)
{
    std::istringstream stream(text);
    Set result;
    char ch;

    stream >> ch;
    if (ch != '{')
    {
        throw std::invalid_argument("Ожидалась '{' в начале");
    }

    while (true)
    {
        stream >> std::ws;
        if (stream.peek() == '}')
        {
            stream.get();
            break;
        }

        if (stream.peek() == '{')
        {
            std::string nested;
            int depth = 0;
            while (stream.get(ch))
            {
                nested += ch;
                if (ch == '{')
                    ++depth;
                if (ch == '}')
                {
                    --depth;
                    if (depth == 0)
                        break;
                }
            }
            result.add(std::make_shared<Set>(Set::fromString(nested)));
        }
        else
        {
            std::string token;
            while (stream.peek() != ',' &&
                   stream.peek() != '}' &&
                   stream.peek() != std::char_traits<char>::eof())
            {
                stream.get(ch);
                token += ch;
            }

            std::size_t begin = token.find_first_not_of(" \t");
            std::size_t end = token.find_last_not_of(" \t");
            if (begin != std::string::npos)
            {
                token = token.substr(begin, end - begin + 1);
            }
            if (!token.empty())
            {
                result.add(std::make_shared<Atom>(token));
            }
        }

        stream >> std::ws;
        if (stream.peek() == ',')
        {
            stream.get();
        }
    }

    return result;
}