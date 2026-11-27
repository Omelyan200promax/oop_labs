#include "lab2/people/Role.hpp"

Role::Role(std::string title, int accessLevel) : title_(title), accessLevel_(accessLevel) {}
bool Role::hasAccess(int requiredLevel) const { return accessLevel_ >= requiredLevel; }
std::string Role::getTitle() const { return title_; }
int Role::getAccessLevel() const { return accessLevel_; }