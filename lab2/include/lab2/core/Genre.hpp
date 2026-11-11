#pragma once
#include <string>

class Genre
{
private:
    std::string name_;
    std::string description_;

public:
    Genre(std::string name, std::string description);
    std::string getDescription() const;
};
