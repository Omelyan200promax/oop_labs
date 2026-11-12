#pragma once
#include <string>

class CoverType
{
private:
    std::string typeName_;
    bool isHard_;

public:
    CoverType(std::string typeName, bool isHard);
    bool isHardCover() const;
};
