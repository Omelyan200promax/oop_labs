#pragma once
#include <string>

class Price
{
private:
    double amount_;
    std::string currency_;

public:
    Price(double amount, std::string currency);
    void applyDiscount(double percent);
    std::string toString() const;
};
