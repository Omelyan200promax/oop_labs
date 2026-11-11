#pragma once
#include <string>

class Dimensions
{
private:
    double length_;
    double width_;
    double height_;

public:
    Dimensions(double length, double width, double height);
    double getVolume() const;
    bool canFitIn(double maxVolume) const;
    std::string toString() const;
};
