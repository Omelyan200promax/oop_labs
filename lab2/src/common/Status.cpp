#include "lab2/common/Status.hpp"
Status::Status(std::string name) : name_(name) {}
std::string Status::getName() const { return name_; }
