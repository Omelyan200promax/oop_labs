#include "lab2/common/LogEntry.hpp"
LogEntry::LogEntry(std::string action) : action_(action) {}
std::string LogEntry::getAction() const { return action_; }
