#pragma once
#include <string>

class Category
{
private:
    std::string name_;
    std::string description_;

public:
    Category(std::string name, std::string description);
    std::string getName() const;
};
