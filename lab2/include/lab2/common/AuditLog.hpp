#pragma once
#include <vector>
#include <string>
#include "lab2/common/LogEntry.hpp"

class AuditLog
{
private:
    std::vector<LogEntry> records_;

public:
    void addRecord(std::string action);
    void printLog() const;
};
