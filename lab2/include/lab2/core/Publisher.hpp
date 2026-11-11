#pragma once
#include <string>

class Publisher
{
private:
    std::string name_;
    std::string city_;

public:
    Publisher(std::string name, std::string city);
    std::string getInfo() const;
};
