#pragma once
#include <string>

class CustomDate
{
private:
    int day_;
    int month_;
    int year_;

public:
    CustomDate(int day, int month, int year);
    std::string toString() const;
    bool isLeapYear() const;
};
