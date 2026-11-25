#pragma once
#include <string>
class Status
{
private:
    std::string name_;

public:
    Status(std::string name);
    std::string getName() const;
};
