#pragma once
#include "lab2/common/Price.hpp"
#include <string>

class Penalty
{
private:
    std::string reason_;
    Price amount_;

public:
    Penalty(std::string reason, Price amount);
    void applyPenalty();
};
