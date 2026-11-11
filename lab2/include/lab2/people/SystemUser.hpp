#pragma once
#include <string>
#include "lab2/people/Role.hpp"

class SystemUser
{
private:
    std::string login_;
    Role role_;

public:
    SystemUser(std::string login, Role role);
    bool loginAs(int requiredLevel) const;
};
