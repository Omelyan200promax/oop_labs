#pragma once
#include <string>

class Equipment
{
private:
    std::string name_;
    bool isWorking_;

public:
    Equipment(std::string name, bool isWorking);
    bool checkStatus() const;
    std::string getName() const;
    void repair();
};
