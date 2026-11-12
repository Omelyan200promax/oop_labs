#include "lab2/core/CoverType.hpp"

CoverType::CoverType(std::string typeName, bool isHard) : typeName_(typeName), isHard_(isHard) {}
bool CoverType::isHardCover() const { return isHard_; }
