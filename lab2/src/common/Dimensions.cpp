#include "lab2/common/Dimensions.hpp"
#include "lab2/exceptions/InvalidDimensionsException.hpp"
#include <sstream>

Dimensions::Dimensions(double length, double width, double height)
{
    if (length <= 0 || width <= 0 || height <= 0)
    {
        throw InvalidDimensionsException("Размеры должны быть положительными");
    }
    length_ = length;
    width_ = width;
    height_ = height;
}

double Dimensions::getVolume() const
{
    return length_ * width_ * height_;
}

bool Dimensions::canFitIn(double maxVolume) const
{
    return getVolume() <= maxVolume;
}

std::string Dimensions::toString() const
{
    std::ostringstream os;
    os << length_ << "x" << width_ << "x" << height_;
    return os.str();
}
