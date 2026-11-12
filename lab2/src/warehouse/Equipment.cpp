#include "lab2/warehouse/Equipment.hpp"

Equipment::Equipment(std::string name, bool isWorking) : name_(name), isWorking_(isWorking) {}
bool Equipment::checkStatus() const { return isWorking_; }
void Equipment::repair() { isWorking_ = true; }
