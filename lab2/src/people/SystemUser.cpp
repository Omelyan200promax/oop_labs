#include "lab2/people/SystemUser.hpp"

SystemUser::SystemUser(std::string login, Role role) : login_(login), role_(role) {}
bool SystemUser::loginAs(int requiredLevel) const { return role_.hasAccess(requiredLevel); }
