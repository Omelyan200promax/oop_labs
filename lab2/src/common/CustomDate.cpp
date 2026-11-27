#include "lab2/common/CustomDate.hpp"
#include <sstream>
#include <iomanip>

CustomDate::CustomDate(int day, int month, int year) : day_(day), month_(month), year_(year) {}

std::string CustomDate::toString() const
{
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << day_ << "."
       << std::setfill('0') << std::setw(2) << month_ << "."
       << year_;
    return os.str();
}

int CustomDate::getDay() const { return day_; }
int CustomDate::getMonth() const { return month_; }
int CustomDate::getYear() const { return year_; }

bool CustomDate::operator<=(const CustomDate &other) const
{
    if (year_ != other.year_)
        return year_ < other.year_;
    if (month_ != other.month_)
        return month_ < other.month_;
    return day_ <= other.day_;
}

bool CustomDate::isLeapYear() const
{
    return (year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0);
}
