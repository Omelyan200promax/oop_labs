#pragma once
#include <string>

class Language
{
private:
    std::string name_;
    std::string isoCode_;

public:
    Language(std::string name, std::string isoCode);
    std::string getCode() const;
};
