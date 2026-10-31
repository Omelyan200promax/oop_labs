#include "lab1/MultiSet.hpp"
#include "lab1/Atom.hpp"
#include <stdexcept>
#include <sstream>

// Находит индекс элемента в векторе или -1, если не найден.
static int findIndex(const std::vector<std::pair<std::shared_ptr<SetElement>, std::size_t>> &elements,
                     std::shared_ptr<SetElement> element)
{
    for (std::size_t i = 0; i < elements.size(); ++i)
    {
        if (elements[i].first->equals(*element))
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Добавление элемента
void MultiSet::add(std::shared_ptr<SetElement> element)
{
    if (element->isPlainSet())
    {
        throw std::invalid_argument("В MultiSet нельзя добавить Set");
    }

    int index = findIndex(elements_, element);
    if (index >= 0)
    {
        elements_[index].second++;
    }
    else
    {
        elements_.push_back({element, 1});
    }
}

// Удаление элемента
void MultiSet::remove(std::shared_ptr<SetElement> element)
{
    int index = findIndex(elements_, element);
    if (index < 0)
    {
        return;
    }

    if (elements_[index].second > 1)
    {
        elements_[index].second--;
    }
    else
    {
        elements_.erase(elements_.begin() + index);
    }
}

// Содержит ли элемент
bool MultiSet::contains(std::shared_ptr<SetElement> element) const
{
    return findIndex(elements_, element) >= 0;
}

std::size_t MultiSet::count(std::shared_ptr<SetElement> element) const
{
    int index = findIndex(elements_, element);
    if (index < 0)
    {
        return 0;
    }
    return elements_[index].second;
}

// Размер мультимножества
std::size_t MultiSet::size() const
{
    std::size_t total = 0;
    for (const auto &pair : elements_)
    {
        total += pair.second;
    }
    return total;
}

// Пустое ли мн-во
bool MultiSet::empty() const
{
    return elements_.empty();
}

std::shared_ptr<SetElement> MultiSet::elementAt(std::size_t index) const
{
    std::size_t counter = 0;
    for (const auto &pair : elements_)
    {
        for (std::size_t k = 0; k < pair.second; ++k)
        {
            if (counter == index)
            {
                return pair.first;
            }
            ++counter;
        }
    }
    throw std::out_of_range("elementAt: индекс вне диапазона");
}

// Объединение
std::shared_ptr<SetLike> MultiSet::unite(const SetLike &other) const
{
    const MultiSet *other_ms = dynamic_cast<const MultiSet *>(&other);
    if (other_ms == nullptr)
    {
        throw std::invalid_argument("MultiSet можно объединять только с MultiSet");
    }

    auto result = std::make_shared<MultiSet>(*this);

    for (std::size_t i = 0; i < other_ms->elements_.size(); ++i)
    {
        auto element = other_ms->elements_[i].first;
        std::size_t other_count = other_ms->elements_[i].second;
        std::size_t this_count = result->count(element);

        if (other_count > this_count)
        {
            std::size_t diff = other_count - this_count;
            for (std::size_t k = 0; k < diff; ++k)
            {
                result->add(element);
            }
        }
    }
    return result;
}

// Пересечение
std::shared_ptr<SetLike> MultiSet::intersect(const SetLike &other) const
{
    const MultiSet *other_ms = dynamic_cast<const MultiSet *>(&other);
    if (other_ms == nullptr)
    {
        throw std::invalid_argument("MultiSet можно пересекать только с MultiSet");
    }

    auto result = std::make_shared<MultiSet>();

    for (const auto &pair : elements_)
    {
        auto element = pair.first;
        std::size_t this_count = pair.second;
        std::size_t other_count = other_ms->count(element);
        std::size_t min_count = (this_count < other_count) ? this_count : other_count;

        for (std::size_t k = 0; k < min_count; ++k)
        {
            result->add(element);
        }
    }
    return result;
}

// Разность
std::shared_ptr<SetLike> MultiSet::difference(const SetLike &other) const
{
    const MultiSet *other_ms = dynamic_cast<const MultiSet *>(&other);
    if (other_ms == nullptr)
    {
        throw std::invalid_argument("MultiSet можно вычитать только из MultiSet");
    }

    auto result = std::make_shared<MultiSet>();

    for (const auto &pair : elements_)
    {
        auto element = pair.first;
        std::size_t this_count = pair.second;
        std::size_t other_count = other_ms->count(element);

        if (this_count > other_count)
        {
            std::size_t diff = this_count - other_count;
            for (std::size_t k = 0; k < diff; ++k)
            {
                result->add(element);
            }
        }
    }
    return result;
}

// Сравнение мультимножеств
bool MultiSet::equals(const SetElement &other) const
{
    const MultiSet *other_ms = dynamic_cast<const MultiSet *>(&other);
    if (other_ms == nullptr)
    {
        return false;
    }
    if (size() != other_ms->size())
    {
        return false;
    }
    for (const auto &pair : elements_)
    {
        if (pair.second != other_ms->count(pair.first))
        {
            return false;
        }
    }
    return true;
}
// вывод в поток
void MultiSet::print(std::ostream &os) const
{
    os << "{";
    bool first = true;
    for (const auto &pair : elements_)
    {
        for (std::size_t k = 0; k < pair.second; ++k)
        {
            if (!first)
            {
                os << ", ";
            }
            pair.first->print(os);
            first = false;
        }
    }
    os << "}";
}

// копирование
std::shared_ptr<SetElement> MultiSet::clone() const
{
    return std::make_shared<MultiSet>(*this);
}

MultiSet &MultiSet::operator+=(const MultiSet &other)
{
    for (const auto &pair : other.elements_)
    {
        for (std::size_t k = 0; k < pair.second; ++k)
        {
            add(pair.first);
        }
    }
    return *this;
}

// Операторы
MultiSet MultiSet::operator+(const MultiSet &other) const
{
    MultiSet result = *this;
    result += other;
    return result;
}

MultiSet &MultiSet::operator*=(const MultiSet &other)
{
    MultiSet result;
    for (const auto &pair : elements_)
    {
        std::size_t other_count = other.count(pair.first);
        std::size_t min_count = (pair.second < other_count) ? pair.second : other_count;
        for (std::size_t k = 0; k < min_count; ++k)
        {
            result.add(pair.first);
        }
    }
    *this = result;
    return *this;
}

MultiSet MultiSet::operator*(const MultiSet &other) const
{
    MultiSet result = *this;
    result *= other;
    return result;
}

MultiSet &MultiSet::operator-=(const MultiSet &other)
{
    MultiSet result;
    for (const auto &pair : elements_)
    {
        std::size_t other_count = other.count(pair.first);
        if (pair.second > other_count)
        {
            std::size_t diff = pair.second - other_count;
            for (std::size_t k = 0; k < diff; ++k)
            {
                result.add(pair.first);
            }
        }
    }
    *this = result;
    return *this;
}

MultiSet MultiSet::operator-(const MultiSet &other) const
{
    MultiSet result = *this;
    result -= other;
    return result;
}

bool MultiSet::operator==(const MultiSet &other) const
{
    return equals(other);
}

bool MultiSet::operator!=(const MultiSet &other) const
{
    return !(*this == other);
}

std::size_t MultiSet::operator[](std::shared_ptr<SetElement> element) const
{
    return count(element);
}

std::ostream &operator<<(std::ostream &os, const MultiSet &multiset)
{
    multiset.print(os);
    return os;
}

// булеан
std::vector<std::shared_ptr<SetLike>> MultiSet::powerSet() const
{
    std::vector<std::shared_ptr<SetLike>> result;
    auto subset = std::make_shared<MultiSet>();
    result.push_back(subset);
    buildPowerSet(result, 0, subset);
    return result;
}

void MultiSet::buildPowerSet(std::vector<std::shared_ptr<SetLike>> &result,
                             std::size_t index,
                             std::shared_ptr<MultiSet> current) const
{
    if (index == elements_.size())
    {
        return;
    }

    auto element = elements_[index].first;
    std::size_t max_count = elements_[index].second;

    for (std::size_t k = 1; k <= max_count; ++k)
    {
        current->add(element);
        auto copy = std::make_shared<MultiSet>(*current);
        result.push_back(copy);
        buildPowerSet(result, index + 1, copy);
    }

    auto copy = std::make_shared<MultiSet>(*current);
    buildPowerSet(result, index + 1, copy);
}

MultiSet MultiSet::fromString(const std::string &text)
{
    std::istringstream stream(text);
    MultiSet result;
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
            result.add(std::make_shared<MultiSet>(MultiSet::fromString(nested)));
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