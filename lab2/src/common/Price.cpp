#include "lab2/common/Price.hpp"
#include <sstream>
#include <stdexcept>

Price::Price(double amount, std::string currency) : currency_(currency)
{
    if (amount < 0)
        throw std::invalid_argument("Цена не может быть отрицательной");
    amount_ = amount;
}
void Price::applyDiscount(double percent)
{
    if (percent > 0 && percent <= 100)
        amount_ = amount_ - (amount_ * percent / 100.0);
}
std::string Price::toString() const
{
    std::ostringstream os;
    os << amount_ << " " << currency_;
    return os.str();
}
double Price::getAmount() const { return amount_; }