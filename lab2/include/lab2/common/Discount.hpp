#pragma once
#include <string>
class Discount
{
private:
    std::string name_;
    double percent_;

public:
    Discount(std::string name, double percent);
    double apply(double price) const;
};
