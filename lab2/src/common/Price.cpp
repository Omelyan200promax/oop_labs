#include "lab2/common/Price.hpp"
#include <sstream>

Price::Price(double amount, std::string currency) : amount_(amount), currency_(currency) {}

void Price::applyDiscount(double percent)
{
    if (percent > 0 && percent <= 100)
    {
        amount_ = amount_ - (amount_ * percent / 100.0);
    }
}

std::string Price::toString() const
{
    std::ostringstream os;
    os << amount_ << " " << currency_;
    return os.str();
}
