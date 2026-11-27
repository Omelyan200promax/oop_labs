#include "lab2/common/AuditLog.hpp"
#include <iostream>

void AuditLog::addRecord(std::string action)
{
    records_.push_back(LogEntry(action));
}
void AuditLog::printLog() const
{
    if (records_.empty())
    {
        std::cout << "Журнал пуст.\n";
        return;
    }
    for (const auto &r : records_)
        std::cout << "- " << r.getAction() << "\n";
}