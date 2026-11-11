#pragma once
#include <string>

class Role
{
private:
    std::string title_;
    int accessLevel_;

public:
    Role(std::string title, int accessLevel);
    bool hasAccess(int requiredLevel) const;
};
