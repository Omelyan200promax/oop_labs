#pragma once
#include <string>
class LogEntry
{
private:
    std::string action_;

public:
    LogEntry(std::string action);
    std::string getAction() const;
};
